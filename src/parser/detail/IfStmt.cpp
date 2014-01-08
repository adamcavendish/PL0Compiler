#include <parser/detail/IfStmt.hpp>
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
#include <parser/detail/CondStmt.hpp>
#include <parser/detail/Statement.hpp>

namespace PL0
{

bool
IfStmt::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat the 'if' token

	auto condstmt = auc::make_unique<CondStmt>();
	if(!condstmt->parse(os, toker))
		flag = false;
	m_condition_node = std::move(condstmt);

	if(flag == true) {
		if(toker->token() != Token::tk_then) {
			flag = false;
			parse_error(os, toker, "Expect `then` token after if");
		} else {
			 toker->next(); // eat `then` token
		}//if-else
	}//if

	if(flag == true) {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, toker))
			flag = false;
		m_iftrue_node = std::move(stmt);
	}//if

	return flag;
}//parse(os, toker)

void
IfStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "IfStmt " << this->position_str() << std::endl;

	if(m_condition_node)
		m_condition_node->pretty_print(os, indent+1);

	if(m_iftrue_node)
		m_iftrue_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

