#include <parser/detail/VarDeclStmt.hpp>
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
VarDeclStmt::parse(std::shared_ptr<Tokenizer> toker) override {
	bool flag = true;

	toker->next(); // eat 'var' token

	while(true) {
		auto var = auc::make_unique<VarDecl>();
		if(var->parse(toker)) {
			m_node_vec.push_back(std::move(var));
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
		parse_error(toker, "A variable declaration statement must end with a ';'");
		flag = false;
	}//if-else

	return flag;
}//parse(toker)

}//namespace PL0

