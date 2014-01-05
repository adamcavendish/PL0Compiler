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
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0 {

class Tokenizer;

bool
BlockUnit::parse(std::shared_ptr<Tokenizer> toker) override {
	bool flag = true;

	if(toker->token() == Token::tk_const) {
		auto cdecl = auc::make_unique<ConstDeclStmt>();
		if(cdecl->parse(toker)) {
			m_const_decl_stmt = cdecl;
		} else {
			flag = false;
		}//if-else
	} else if(toker->token() == Token::tk_var) {
		auto vdecl = auc::make_unique<VarDeclStmt>();
		if(vdecl->parse(toker)) {
			m_var_decl_stmt = vdecl;
		} else {
			flag = false;
		}//if-else
	}//if-else
	
	return flag;
}//parse(toker)

}//namespace PL0

