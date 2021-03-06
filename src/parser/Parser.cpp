#include <parser/Parser.hpp>
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
#include <parser/detail/ProgramUnit.hpp>

namespace PL0
{

bool
Parser::parse(std::ostream & os, std::shared_ptr<Context> context) {
	bool flag = true;

	context->getTokenizer()->next(); // start tokenizing

	auto prog = auc::make_unique<ProgramUnit>();
	if(!prog->parse(os, context))
		flag = false;

	m_genesis = std::move(prog);

	return flag;
}//parse(os, context)

void
Parser::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "TranslationUnit" << std::endl;

	if(m_genesis)
		m_genesis->pretty_print(os, indent + 1);
}//pretty_print(os, indent)

llvm::Value *
Parser::llvm_generate(std::shared_ptr<Context> context) const {
    if(m_genesis)
	    return m_genesis->llvm_generate(context);
    return nullptr;
}//llvm_generate(context)

}//namespace PL0

