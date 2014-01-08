#include <parser/detail/BlockUnit.hpp>
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
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/ConstDeclStmt.hpp>
#include <parser/detail/VarDeclStmt.hpp>
#include <parser/detail/Expression.hpp>

namespace PL0 {

bool
BlockUnit::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_const) {
		auto cdecl = auc::make_unique<ConstDeclStmt>();
		if(!cdecl->parse(os, toker))
			flag = false;
		m_const_decl_stmt = std::move(cdecl);
	}//if
	
	if(toker->token() == Token::tk_var) {
		auto vdecl = auc::make_unique<VarDeclStmt>();
		if(!vdecl->parse(os, toker))
			flag = false;
		m_var_decl_stmt = std::move(vdecl);
	}//if-else

	// @TODO grammar is not complete
	auto expr = auc::make_unique<Expression>();
	if(!expr->parse(os, toker))
		flag = false;
	m_expr = std::move(expr);
	
	return flag;
}//parse(os, toker)

void
BlockUnit::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "BlockUnit " << this->position_str() << std::endl;
	
	if(m_const_decl_stmt)
		m_const_decl_stmt->pretty_print(os, ident+1);
	if(m_var_decl_stmt)
		m_var_decl_stmt->pretty_print(os, ident+1);

	if(m_expr)
		m_expr->pretty_print(os, ident+1);
}//pretty_print(os, ident)

}//namespace PL0

