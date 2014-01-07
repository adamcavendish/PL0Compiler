#include <parser/detail/ConstDeclStmt.hpp>
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
#include <parser/detail/ConstVarDecl.hpp>

namespace PL0
{

class Tokenizer;

bool
ConstDeclStmt::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	bool flag = true;

	toker->next(); // eat 'const' token

	while(true) {
		auto cvar = auc::make_unique<ConstVarDecl>();
		if(cvar->parse(os, toker)) {
			m_node_vec.push_back(std::move(cvar));
		} else {
			flag = false;
			break;
		}//if-else

		if(toker->token() == Token::tk_comma) {
			toker->next(); // eat ',' token
		} else {
			break;
		}//if-else
	}//while
	
	if(flag == true && toker->token() == Token::tk_semicolon) {
		toker->next(); // eat ';' token
	} else {
		parse_error(toker, "A const declaration statement must end in a ';'");
		flag = false;
	}//if-else
	
	return flag;
}//parse(os, toker)

void
ConstDeclStmt::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "ConstDeclStmt" << std::endl;
	for(const auto & i : m_node_vec)
		i->pretty_print(os, ident + 1);
}//pretty_print(os, ident)

}//namespace PL0

