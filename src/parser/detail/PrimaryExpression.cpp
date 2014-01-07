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
#include <parser/HelperFunctions.hpp>
#include <parser/detail/Expression.hpp>
#include <parser/detail/IdentRefExpression.hpp>
#include <parser/detail/IntegerLiteral.hpp>

namespace PL0
{

bool
PrimaryExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	bool flag = true;

	if(toker->token() == Token::tk_identifier) {
		auto ident = auc::make_unique<IdentRefExpression>();
		if(!ident->parse(os, toker))
			flag = false;

		m_node = std::move(ident);
	} else if(toker->token() == Token::tk_number) {
		auto num = auc::make_unique<IntegerLiteral>();
		if(!num->parse(os, toker))
			flag =false;

		m_node = std::move(num);
	} else if(toker->token() == Token::tk_lparenthesis) {
		toker->next(); // eat the '('

		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, toker))
			flag = false;

		m_node = std::move(expr);

		if(toker->token() != Token::tk_rparenthesis) {
			parse_error(toker, "Expect a ')' here.");
		} else {
			toker->next(); // eat the current ')'
		}//if-else
	} else {
		flag = false;
		parse_error(toker, "Expect either an identifier, or a number, or a parenthesized expression here.");
	}//if-else

	return flag;
}//parse(os, toker)

void
PrimaryExpression::pretty_print(std::ostream & os, std::size_t ident) const {
	if(m_node)
		m_node->pretty_print(os, ident + 1);
}//pretty_print(os, ident)

}//namespace PL0

