#include <parser/detail/UnaryExpression.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/PrimaryExpression.hpp>

namespace PL0
{

bool
UnaryExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_plus) {
		m_unary_op = '+';
		toker->next();
	} else if(toker->token() == Token::tk_minus) {
		m_unary_op = '-';
		toker->next();
	} else {
		m_unary_op = '\0';
	}//if-else

	auto prim = auc::make_unique<PrimaryExpression>();
	if(!prim->parse(os, context))
		flag = false;
	m_node = std::move(prim);

	return flag;
}//parse(os, context)

void
UnaryExpression::pretty_print(std::ostream & os, std::size_t indent) const {
#ifndef NDEBUG
	os << std::string(indent, '\t') << "UnaryExpression(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	if(m_unary_op != '\0') {
		os << std::string(indent, '\t') << "UnaryExpression "
			<< this->position_str() << " '" << m_unary_op << "'" << std::endl;
		if(m_node)
			m_node->pretty_print(os, indent+1);
	} else {
		if(m_node)
			m_node->pretty_print(os, indent);
	}//if-else
}//pretty_print(os, indent)

llvm::Value *
UnaryExpression::llvm_generate(std::shared_ptr<Context> context) const {
	auto ret = m_node->llvm_generate(context);
    if(ret == nullptr) {
        generate_error(std::cerr, context, "UnaryExpression::llvm_generate error");
    }//if

    if(m_unary_op == '-') {
        // create a sub from 0: `%unaryminus = sub nsw i32 0, %ret`
        ret = context->getIRBuilder_llvm()->CreateSub(
                llvm::ConstantInt::get(
                    *(context->getLLVMContext_llvm()),
                    llvm::APInt(32, 0, true)),
                ret,
                "unaryminus");
        if(ret == nullptr) {
            generate_error(std::cerr, context,
                    "UnaryExpression::llvm_generate error CreateSub failed");
            std::abort();
        }//if
    }//if

    return ret;
}//llvm_generate(context)

}//namespace PL0

