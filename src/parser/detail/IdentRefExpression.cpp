#include <parser/detail/IdentRefExpression.hpp>
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
IdentRefExpression::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auc_UNUSED(os);
	auto toker = context->getTokenizer();

	m_position = toker->position();

	m_ident = toker->word();
	toker->next(); // eat the identifer token
	return true;
}//parse(os, context) 

void
IdentRefExpression::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "IdentRefExpression "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

llvm::Value *
IdentRefExpression::llvm_generate(std::shared_ptr<Context> context) const {
	auto ret = context->lookupVariable_llvm(m_ident);
    if(ret == nullptr) {
        generate_error(std::cerr, context, "Undefined reference of variable: " + m_ident);
    }//if

    return ret;
}//llvm_generate(context)

}//namespace PL0

