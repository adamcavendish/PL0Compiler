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
#include <parser/detail/ProcedureUnit.hpp>
#include <parser/detail/Statement.hpp>

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

	while(flag == true && toker->token() == Token::tk_procedure) {
		auto proc_unit = auc::make_unique<ProcedureUnit>();
		if(!proc_unit->parse(os, toker))
			flag = false;
		m_procedures.push_back(std::move(proc_unit));
	}//while

	if(flag == true) {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, toker))
			flag = false;
		m_statement = std::move(stmt);
	}//if
	
	return flag;
}//parse(os, toker)

void
BlockUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "BlockUnit " << this->position_str() << std::endl;
	
	if(m_const_decl_stmt)
		m_const_decl_stmt->pretty_print(os, indent+1);
	if(m_var_decl_stmt)
		m_var_decl_stmt->pretty_print(os, indent+1);
	for(const auto & i : m_procedures)
		i->pretty_print(os, indent+1);
	if(m_statement)
		m_statement->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

