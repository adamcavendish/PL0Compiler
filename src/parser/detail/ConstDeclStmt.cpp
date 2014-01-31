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
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/ConstVarDecl.hpp>

namespace PL0
{

class Context;

bool
ConstDeclStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat 'const' token

	while(true) {
		auto cvar = auc::make_unique<ConstVarDecl>();
		if(!cvar->parse(os, context)) {
			flag = false;
			m_node_vec.push_back(std::move(cvar));
			break;
		} else {
			m_node_vec.push_back(std::move(cvar));
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
		parse_error(os, context, "A const declaration statement must end in a ';'");
		flag = false;
	}//if-else
	
	return flag;
}//parse(os, context)

void
ConstDeclStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ConstDeclStmt " << this->position_str() << std::endl;

	for(const auto & i : m_node_vec) {
		if(i)
			i->pretty_print(os, indent+1);
	}//for
}//pretty_print(os, indent)

llvm::Value *
ConstDeclStmt::llvm_generate(std::shared_ptr<Context> context) const {
	llvm::Value * const_decl_gen = nullptr;
	for(auto & i : m_node_vec) {
		if(i) {
			const_decl_gen = i->llvm_generate(context);
			if(const_decl_gen == nullptr) {
				generate_error(std::cerr, context, "ConstDeclStmt->ConstVarDecl llvm_generate error");
			}//if
		}//if
	}//for

    return llvm::Constant::getNullValue(
            llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())));
}//llvm_generate(context)

}//namespace PL0

