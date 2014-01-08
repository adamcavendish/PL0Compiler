#include <parser/detail/CondStmt.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
// C-STL
#include <cstdlib>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/Expression.hpp>

namespace PL0
{

bool
CondStmt::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_odd) {
		m_condition_op = Token::tk_odd;
		toker->next(); // eat current token 'odd'

		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, toker))
			flag = false;
		m_expr_node1 = std::move(expr);
	} else {
		auto left_expr = auc::make_unique<Expression>();
		if(!left_expr->parse(os, toker))
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
			parse_error(os, toker, "Unexpected Comparison Operator Here.");
		} else {
			m_condition_op = toker->token();
			toker->next(); // eat the comparison operator
		}//if-else

		if(flag == true) {
			auto right_expr = auc::make_unique<Expression>();
			if(!right_expr->parse(os, toker))
				flag = false;
			m_expr_node2 = std::move(right_expr);
		}//if
	}//if-else

	return flag;
}//parse(os, toker)

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
			std::cerr << "Parser Error: Unexpected Condition Opeartor" << std::endl;
			std::abort();
		}//switch
		os << "'"<< std::endl;

		if(m_expr_node1)
			m_expr_node1->pretty_print(os, indent+1);
		if(m_expr_node2)
			m_expr_node2->pretty_print(os, indent+1);
	}//if-else
}//pretty_print(os, indent)

}//namespace PL0

