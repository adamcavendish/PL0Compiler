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
#include <parser/HelperFunctions.hpp>
#include <parser/detail/PrimaryExpression.hpp>

namespace PL0
{

bool
UnaryExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
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
	if(!prim->parse(os, toker))
		flag = false;
	m_node = std::move(prim);

	return flag;
}//parse(os, toker)

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

}//namespace PL0

