#include <parser/detail/CondStmt.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <vector>
// C-STL
#include <cstdlib>
#include <cassert>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/Expression.hpp>

namespace PL0
{

bool
CondStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_odd) {
		m_condition_op = Token::tk_odd;
		toker->next(); // eat current token 'odd'

		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, context))
			flag = false;
		m_expr_node1 = std::move(expr);
        m_expr_node2.reset();
	} else {
		auto left_expr = auc::make_unique<Expression>();
		if(!left_expr->parse(os, context))
			flag = false;
		m_expr_node1 = std::move(left_expr);

		if(toker->token() != tk_equal &&
				toker->token() != tk_notequal &&
				toker->token() != tk_less &&
				toker->token() != tk_lessequal &&
				toker->token() != tk_greater &&
				toker->token() != tk_greaterequal)
		{
			flag = false;
			parse_error(os, context, "Unexpected Comparison Operator Here.");
		} else {
			m_condition_op = toker->token();
			toker->next(); // eat the comparison operator
		}//if-else

		if(flag == true) {
			auto right_expr = auc::make_unique<Expression>();
			if(!right_expr->parse(os, context))
				flag = false;
			m_expr_node2 = std::move(right_expr);
		}//if
	}//if-else

	return flag;
}//parse(os, context)

void
CondStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	if(m_condition_op == Token::tk_odd) {
		os << std::string(indent, '\t') << "CondStmt " << this->position_str() 
			<< " 'odd'"<< std::endl;

		if(m_expr_node1)
			m_expr_node1->pretty_print(os, indent+1);
	} else {
		os << std::string(indent, '\t') << "CondStmt " << this->position_str() 
			<< " '";
		switch(m_condition_op) {
		case tk_equal:
			os << "=";
			break;
		case tk_notequal:
			os << "#";
			break;
		case tk_less:
			os << "<";
			break;
		case tk_lessequal:
			os << "<=";
			break;
		case tk_greater:
			os << ">";
			break;
		case tk_greaterequal:
			os << ">=";
			break;
		default:
			assert(0 && "Parser Error: Unexpected Condition Opeartor");
			std::abort();
		}//switch
		os << "'"<< std::endl;

		if(m_expr_node1)
			m_expr_node1->pretty_print(os, indent+1);
		if(m_expr_node2)
			m_expr_node2->pretty_print(os, indent+1);
	}//if-else
}//pretty_print(os, indent)

llvm::Value *
CondStmt::llvm_generate(std::shared_ptr<Context> context) const {
    llvm::Value * ret = nullptr;
    llvm::Value * expr1gen = nullptr;
    llvm::Value * expr2gen = nullptr;

	auto generate_odd_IR = [&]() -> llvm::Value * {
        // bitand expr1gen with 0x01 to check whether it is odd or not
        auto llvmret = context->getIRBuilder_llvm()->CreateAnd(
                expr1gen,
                llvm::ConstantInt::get(
                    *(context->getLLVMContext_llvm()),
                    llvm::APInt(32, 1, true)),
                "oddand");
        if(llvmret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateAnd error");
            std::abort();
        }//if

        // cmp bitand-result with 1: true -- odd; false -- non-odd
        llvm::Value * odd_ret = context->getIRBuilder_llvm()->CreateICmpEQ(
                llvmret,
                llvm::ConstantInt::get(
                    *(context->getLLVMContext_llvm()),
                    llvm::APInt(32, 1, true)),
                "oddcmp");
        if(llvmret == nullptr) {
            generate_error(std::cerr, context, "CondStmt:llvm_generate CreateICmpEQ error");
            std::abort();
        }//if

        return odd_ret;
    };//lambda generate_odd_IR

    auto generate_equal_IR = [&]() -> llvm::Value * {
        llvm::Value * equret = context->getIRBuilder_llvm()->CreateICmpEQ(
                expr1gen, expr2gen, "op_equ");
        if(equret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpEQ Error");
            std::abort();
        }//if
        return equret;
    };//lambda generate_equal_IR

    auto generate_notequal_IR = [&]() -> llvm::Value * {
        llvm::Value * nequret = context->getIRBuilder_llvm()->CreateICmpNE(
                expr1gen, expr2gen, "op_notequ");
        if(nequret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpNE Error");
            std::abort();
        }//if
        return nequret;
    };//lambda generate_notequal_IR

    auto generate_less_IR = [&]() -> llvm::Value * {
        llvm::Value * lessret = context->getIRBuilder_llvm()->CreateICmpSLT(
                expr1gen, expr2gen, "op_less");
        if(lessret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpSLT Error");
            std::abort();
        }//if
        return lessret;
    };//lambda generate_less_IR

    auto generate_lessequal_IR = [&]() -> llvm::Value * {
        llvm::Value * lessequalret = context->getIRBuilder_llvm()->CreateICmpSLE(
                expr1gen, expr2gen, "op_lessequal");
        if(lessequalret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpSLE Error");
            std::abort();
        }//if
        return lessequalret;
    };//lambda generate_lessequal_IR

    auto generate_greater_IR = [&]() -> llvm::Value * {
        llvm::Value * greaterret = context->getIRBuilder_llvm()->CreateICmpSGT(
                expr1gen, expr2gen, "op_greater");
        if(greaterret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpSGT Error");
            std::abort();
        }//if
        return greaterret;
    };//lambda generate_greater_IR

    auto generate_greaterequal_IR = [&]() -> llvm::Value * {
        llvm::Value * greaterequalret = context->getIRBuilder_llvm()->CreateICmpSGE(
                expr1gen, expr2gen, "op_greaterequal");
        if(greaterequalret == nullptr) {
            generate_error(std::cerr, context, "CondStmt::llvm_generate CreateICmpSGE Error");
            std::abort();
        }//if
        return greaterequalret;
    };//lambda generate_greaterequal_IR

    // --------------------------------------------------
    // main part
    // --------------------------------------------------

    // generate two nodes
    expr1gen = m_expr_node1->llvm_generate(context);
    if(expr1gen == nullptr) {
        generate_error(std::cerr, context, "CondStmt->Expression llvm_generate error");
        return nullptr;
    }//if
    if(m_condition_op != Token::tk_odd) {
        expr2gen = m_expr_node2->llvm_generate(context);
        if(expr2gen == nullptr) {
            generate_error(std::cerr, context, "CondStmt->Expression llvm_generate error");
            return nullptr;
        }//if
    }//if

    switch(m_condition_op) {
    case Token::tk_odd:
        ret = generate_odd_IR();
        break;
    case Token::tk_equal:
        ret = generate_equal_IR();
        break;
    case Token::tk_notequal:
        ret = generate_notequal_IR();
        break;
    case Token::tk_less:
        ret = generate_less_IR();
        break;
    case Token::tk_lessequal:
        ret = generate_lessequal_IR();
        break;
    case Token::tk_greater:
        ret = generate_greater_IR();
        break;
    case Token::tk_greaterequal:
        ret = generate_greaterequal_IR();
        break;
    default:
        assert(0 && "CondStmt llvm_generate: Unexptected condition operator");
        std::abort();
    }//switch-case
    
    return ret;
}//llvm_generate(context)

}//namespace PL0

