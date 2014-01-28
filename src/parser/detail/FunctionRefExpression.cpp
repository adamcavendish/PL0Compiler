#include <parser/detail/FunctionRefExpression.hpp>
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
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace PL0
{

bool
FunctionRefExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auc_UNUSED(os);
	auto toker = context->getTokenizer();

	m_position = toker->position();

	m_ident = toker->word();
	toker->next(); // eat current function identifier
	return true;
}//parse(os, context)

void
FunctionRefExpression::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "FunctionRefExpression "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

llvm::Value *
FunctionRefExpression::llvm_generate(std::shared_ptr<Context> context) const {
	return context->lookupFunction_llvm(m_ident);
}//llvm_generate(context)

}//namespace PL0

