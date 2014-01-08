#include <parser/detail/ProcedureDecl.hpp>
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

namespace PL0
{

bool
ProcedureDecl::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	if(toker->token() != Token::tk_procedure) {
		flag = false;
		parse_error(os, toker, "Expect `procedure` token here.");
	} else {
		toker->next(); // eat 'procedure' token
	}//if-else

	if(flag == true) {
		if(toker->token() != Token::tk_identifier) {
			flag = false;
			parse_error(os, toker, "A procedure declaration should observe identifier declaration rule.");
		} else {
			m_ident = toker->word();
			toker->next(); // eat the current procedure identifier
		}//if-else
	}//if

	if(flag == true) {
		if(toker->token() != Token::tk_semicolon) {
			flag = false;
			parse_error(os, toker, "A procedure declaration should end with a ';'");
		} else {
			toker->next(); // eat the current ';' token
		}//if-else
	}//if

	return flag;
}//parse(os, toker)

void
ProcedureDecl::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t')
		<< "ProcedureDecl " << this->position_str() << " "
		<< m_ident << std::endl;
}//pretty_print(os, indent)

}//namespace PL0

