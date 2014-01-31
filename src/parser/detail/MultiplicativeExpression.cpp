#include <parser/detail/MultiplicativeExpression.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <functional>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/UnaryExpression.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace PL0
{

bool
MultiplicativeExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	if(flag == true) {
		auto unary = auc::make_unique<UnaryExpression>();
		if(!unary->parse(os, context))
			flag = false;
		m_node_first = std::move(unary);
	}//if

	while(flag == true) {
		std::pair<Operator, std::unique_ptr<ParserBase>> node;

		if(toker->token() == Token::tk_multiply) {
			node.first.m_op = '*';
			node.first.m_position = toker->position();
		} else if(toker->token() == Token::tk_divide) {
			node.first.m_op = '/';
			node.first.m_position = toker->position();
		} else {
			break;
		}//if-else
		toker->next(); // Eat the current operator

		auto unary = auc::make_unique<UnaryExpression>();
		if(!unary->parse(os, context))
			flag = false;

			node.second = std::move(unary);
			m_nodes.push_back(std::move(node));
	}//while

	return flag;
}//parse(os, context)

void
MultiplicativeExpression::pretty_print(std::ostream & os, std::size_t indent) const {
#ifndef NDEBUG
	os << std::string(indent, '\t') << "MultiplicativeExpression(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	std::function<void(int, std::size_t)> print_helper = [&](int rec, std::size_t rec_indent) {
		os << std::string(rec_indent, '\t')
			<< "BinaryOperator <" << m_nodes[rec].first.m_position.first << ","
			<< m_nodes[rec].first.m_position.second << ">"
			<< " '" << m_nodes[rec].first.m_op << "'" << std::endl;

		if(rec == 0) {
			if(m_node_first)
				m_node_first->pretty_print(os, rec_indent+1);
			if(m_nodes[0].second)
				m_nodes[0].second->pretty_print(os, rec_indent+1);
			return;
		}//if

		print_helper(rec-1, rec_indent+1);

		if(m_nodes[rec].second)
			m_nodes[rec].second->pretty_print(os, rec_indent+1);
	};//lambda print_helper(rec)

	auto sz = m_nodes.size();
	if(sz > 0) {
		print_helper(sz-1, indent);
	} else {
		if(m_node_first)
			m_node_first->pretty_print(os, indent);
	}//if-else
}//pretty_print(os, indent)

llvm::Value *
MultiplicativeExpression::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;
    llvm::Value * ret = nullptr;

	auto generate_one_node = [&](const std::unique_ptr<ParserBase> & node) -> llvm::Value * {
		if(node) {
			llvm::Value * unaryexpr = node->llvm_generate(context);
				if(unaryexpr == nullptr) {
					generate_error(std::cerr, context,
							"MultiplicativeExpression->UnaryExpression llvm_generate error");
					flag = false;
				}//if
				return unaryexpr;
		}//if
		return nullptr;
	};//lambda generate_one_node(node)

	auto generate_binary_op_IR = [&](const char op, llvm::Value * L, llvm::Value * R) -> llvm::Value * {
		llvm::Value * ret = nullptr;
		if(op == '*') {
			ret = context->getIRBuilder_llvm()->CreateMul(L, R, "multmp");
			if(ret == nullptr) {
				generate_error(std::cerr, context,
						"MultiplicativeExpression::llvm_generate error CreateMul failed");
				std::abort();
			}//if
		} else if(op == '/') {
			ret = context->getIRBuilder_llvm()->CreateSDiv(L, R, "sdivtmp");
			if(ret == nullptr) {
				generate_error(std::cerr, context,
						"MultiplicativeExpression::llvm_generate error CreateSDiv failed");
				std::abort();
			}//if
		} else {
			generate_error(std::cerr, context,
					std::string("MultiplicativeExpression::llvm_generate error: encounter unknown operator '")
					+ op + "'");
			flag = false;
			return nullptr;
		}//if-else
		return ret;
	};//lambda generate_binary_op_IR(op, L, R)

	std::function<llvm::Value *(int)> generate_helper = [&](int rec) -> llvm::Value * {
		llvm::Value * L = nullptr;
		llvm::Value * R = nullptr;

		if(flag == false)
			return nullptr;

		if(rec == 0) {
			if((L = generate_one_node(m_node_first)) == nullptr)
				return nullptr;
			
			if((R = generate_one_node(m_nodes[0].second)) == nullptr)
				return nullptr;
		} else {
            if((L = generate_helper(rec-1)) == nullptr)
                return nullptr;

            if((R = generate_one_node(m_nodes[rec].second)) == nullptr)
                return nullptr;
        }//if-else

		auto ret = generate_binary_op_IR(m_nodes[rec].first.m_op, L, R);
		return ret;
	};//lambda generate_helper(rec)

	auto sz = m_nodes.size();
	if(sz > 0) {
		ret = generate_helper(sz-1);
	} else {
		ret = generate_one_node(m_node_first);
	}//if-else

	if(flag == true) {
        return ret;
    }//if
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

