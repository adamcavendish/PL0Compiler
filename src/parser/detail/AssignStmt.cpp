#include <parser/detail/AssignStmt.hpp>
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
#include <parser/detail/IdentRefExpression.hpp>
#include <parser/detail/Expression.hpp>

namespace PL0
{

bool
AssignStmt::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	auto identref = auc::make_unique<IdentRefExpression>();
	if(!identref->parse(os, toker))
		flag = false;
	m_assign_left = std::move(identref);

	if(flag == true) {
		if(toker->token() != Token::tk_assign) {
			flag = false;
			parse_error(os, toker, "Expect an assignment operator Here!");
		} else {
			toker->next(); // eat the current ':=' operator
		}//if-else
	}//if
	
	if(flag == true) {
		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, toker))
			flag = false;
		m_assign_right = std::move(expr);
	}//if

	return flag;
}//parse(os, toker)

void
AssignStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "AssignStmt " << this->position_str() << std::endl;

	if(m_assign_left)
		m_assign_left->pretty_print(os, indent+1);
	if(m_assign_right)
		m_assign_right->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

