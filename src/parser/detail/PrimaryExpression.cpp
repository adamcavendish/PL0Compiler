#include <parser/detail/PrimaryExpression.hpp>
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
#include <parser/detail/Expression.hpp>
#include <parser/detail/IdentRefExpression.hpp>
#include <parser/detail/IntegerLiteral.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace PL0
{

bool
PrimaryExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_identifier) {
		auto ident = auc::make_unique<IdentRefExpression>();
		if(!ident->parse(os, context))
			flag = false;

		m_node = std::move(ident);
	} else if(toker->token() == Token::tk_number) {
		auto num = auc::make_unique<IntegerLiteral>();
		if(!num->parse(os, context))
			flag =false;

		m_node = std::move(num);
	} else if(toker->token() == Token::tk_lparenthesis) {
		toker->next(); // eat the '('

		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, context))
			flag = false;

		m_node = std::move(expr);

		if(toker->token() != Token::tk_rparenthesis) {
			parse_error(os, context, "Expect a ')' here.");
		} else {
			toker->next(); // eat the current ')'
		}//if-else
	} else {
		flag = false;
		parse_error(os, context,
				"Expect either an identifier, or a number, or a parenthesized expression here.");
	}//if-else

	return flag;
}//parse(os, context)

void
PrimaryExpression::pretty_print(std::ostream & os, std::size_t indent) const {
#ifndef NDEBUG
	os << std::string(indent, '\t') << "PrimaryExpression(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	if(m_node)
		m_node->pretty_print(os, indent);
}//pretty_print(os, indent)

llvm::Value *
PrimaryExpression::llvm_generate(std::shared_ptr<Context> context) const {
	return m_node->llvm_generate(context);
}//llvm_generate(context)

}//namespace PL0

