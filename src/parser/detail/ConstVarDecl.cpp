#include <parser/detail/ConstVarDecl.hpp>
// STL
#include <iostream>
#include <memory>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/IntegerLiteral.hpp>

namespace PL0
{

bool
ConstVarDecl::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	m_ident = toker->word();

	toker->next(); // eat the current identifier

	if(toker->token() != Token::tk_equal) {
		parse_error(os, context, "expect an '=' here for const identifier initialization");
		flag = false;
	} else {
		toker->next(); // eat the current '='
	}//if-else

	if(flag == true && toker->token() == Token::tk_number) {
		// make_unique was overlooked by c++11, a simple implementation
		auto int_num = auc::make_unique<IntegerLiteral>();
		if(!int_num->parse(os, context))
			flag = false;
		m_node = std::move(int_num);
	} else {
		parse_error(os, context, "A const declearation must be initialized with a integer number.");
		flag = false;
	}//if-else

	return flag;
}//parse(os, context)

void
ConstVarDecl::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ConstVarDecl "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
ConstVarDecl::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::ConstantInt * int_gen = (llvm::ConstantInt *)(m_node->llvm_generate(context));
	if(int_gen == nullptr) {
		generate_error(std::cerr, context, "ConstVarDecl->IntegerLiteral llvm_generate error");
		flag = false;
	}//if

    if(context->createConstant_llvm(m_ident, int_gen) == false) {
        generate_error(std::cerr, context,
                "Redefinition of variable: " + m_ident);
        flag = false;
    }//if

	if(flag == false) {
		return nullptr;
    }//if
	return int_gen;
}//llvm_generate(context)

}//namespace PL0

