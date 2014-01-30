#include <parser/detail/ProcedureRefExpression.hpp>
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
ProcedureRefExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auc_UNUSED(os);
	auto toker = context->getTokenizer();

	m_position = toker->position();

	m_ident = toker->word();
	toker->next(); // eat current function identifier
	return true;
}//parse(os, context)

void
ProcedureRefExpression::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProcedureRefExpression "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

llvm::Value *
ProcedureRefExpression::llvm_generate(std::shared_ptr<Context> context) const {
	llvm::Function * func = context->getModule_llvm()->getFunction(m_ident);
	if(func == nullptr) {
		std::cerr << "Function: " << m_ident << " not found" << std::endl;
	}//if

	return func;
}//llvm_generate(context)

}//namespace PL0

