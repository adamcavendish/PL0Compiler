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
    bool ident_local = context->lookupVariable_local_llvm(m_ident).second;
    bool ident_parent = context->lookupVariable_parent_llvm(m_ident).second;

    // if it's a local identifier, pass
    if(ident_local == false) {
        if(ident_parent == true) {
            // referencing to parent identifiers, need a closure
            context->getClosure().push_back(m_ident);
        } else {
            // if the identifier is not found
            parse_error(os, context, "Undefined reference to variant/constant: " + m_ident);
        }//if-else
    }//if-else

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
    auto processVariable = [&]() -> llvm::Value * {
        llvm::AllocaInst * lookup = context->lookupVariable_local_llvm(m_ident).second;
        if(lookup != nullptr) {
            llvm::LoadInst * loadInst = context->getIRBuilder_llvm()->CreateLoad(lookup, m_ident);
            if(loadInst == nullptr) {
                generate_error(std::cerr, context,
                        "IdentRefExpression::llvm_generate CreateLoad error!");
                std::abort();
            }//if
            return loadInst;
        }//if
        return nullptr;
    };//lambda processVariable

    auto processConstant = [&]() -> llvm::Value * {
        llvm::Constant * constant = context->lookupConstant_local_llvm(m_ident).second;
        if(constant != nullptr) {
            return constant;
        }//if
        return nullptr;
    };//lambda processConstant

    auto processNotFoundInLocal = [&]() -> void {
        if(context->lookupVariable_parent_llvm(m_ident).first == true) {
            generate_error(std::cerr, context,
                    "IndentRefExpression::llvm_generate variable closure error: " + m_ident);
            return;
        }//if
        if(context->lookupConstant_parent_llvm(m_ident).first == true) {
            generate_error(std::cerr, context,
                    "IdentRefExpression::llvm_generate constant closure error: " + m_ident);
            return;
        }//if

        generate_error(std::cerr, context, "Undefined reference to variable/constant: " + m_ident);
    };//lambda processNotFoundInLocal

    llvm::Value * ret = nullptr;

    // --------------------------------------------------
    // main part
    // --------------------------------------------------
    if((ret = processVariable()) != nullptr){
        return ret;
    }//if
    if((ret = processConstant()) != nullptr) {
        return ret;
    }//if

    processNotFoundInLocal();
    return nullptr;
}//llvm_generate(context)

}//namespace PL0

