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
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0
{

class Tokenizer;

bool
ConstDeclStmt::parse(std::shared_ptr<Tokenizer> toker) override {
	bool flag = true;

	toker->next(); // eat 'const' token

	while(true) {
		auto cvar = auc::make_unique<ConstVarDecl>();
		if(cvar->parse(toker)) {
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
}//parse(toker)

}//namespace PL0

