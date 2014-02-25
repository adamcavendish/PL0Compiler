#include <parser/detail/ProcedureDecl.hpp>
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
ProcedureDecl::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	if(toker->token() != Token::tk_procedure) {
		flag = false;
		parse_error(os, context, "Expect `procedure` token here.");
	} else {
		toker->next(); // eat 'procedure' token
	}//if-else

	if(flag == true) {
		if(toker->token() != Token::tk_identifier) {
			flag = false;
			parse_error(os, context, "A procedure declaration should observe identifier declaration rule.");
		} else {
			m_ident = toker->word();
			toker->next(); // eat the current procedure identifier
		}//if-else
	}//if

	if(flag == true) {
		if(toker->token() != Token::tk_semicolon) {
			flag = false;
			parse_error(os, context, "A procedure declaration should end with a ';'");
		} else {
			toker->next(); // eat the current ';' token
		}//if-else
	}//if

    auto insertret = context->getFunctionClosureMap()->insert(
            std::make_pair(m_ident, std::unordered_set<std::string>()));
    if(insertret.second == false) {
        parse_error(os, context, "ProcedureDecl parse error: insert procedure map failed: " + m_ident);
        flag = false;
    }//if
    context->currentFunctionIter() = insertret.first;

	return flag;
}//parse(os, context)

void
ProcedureDecl::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t')
		<< "ProcedureDecl " << this->position_str() << " "
		<< m_ident << std::endl;
}//pretty_print(os, indent)

llvm::Value *
ProcedureDecl::llvm_generate(std::shared_ptr<Context> context) const {
    auto closuresz = context->getFunctionClosureMap()->find(m_ident)->second.size();
#if 1
    std::cerr << "closure size: " << closuresz << std::endl;
#endif
    // closure parameters
    std::vector<llvm::Type *> closure_params(closuresz,
            llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())));

	llvm::FunctionType * FT = llvm::FunctionType::get(
			llvm::Type::getVoidTy(*(context->getLLVMContext_llvm())), closure_params, false);
	llvm::Function * F = llvm::Function::Create(
			FT, llvm::Function::ExternalLinkage, m_ident, context->getModule_llvm().get());
	// prevent from redefinition
	if (F->getName() != m_ident) {
	  // Delete the one we just made
	  F->eraseFromParent();
	  return nullptr;
	}//if

    // get current procedure's closure
    auto && closure = [&] {
        auto findret = context->getFunctionClosureMap()->find(m_ident);
        if(findret == context->getFunctionClosureMap()->end()) {
            generate_error(std::cerr, context, "ProcedureDecl::llvm_generate error: "
                    "cannot get current function in function closure map!");
            std::abort();
        }//if
        return findret->second;
    }();

#if 1
    std::cerr << "procedure decl closure: " << m_ident << std::endl;
#endif

    llvm::Function::arg_iterator AI = F->arg_begin(), AI_end = F->arg_end();
    auto closure_iter = closure.begin();
    while(AI != AI_end) {
#if 1
        std::cerr << "\t" << *closure_iter << std::endl;
#endif
        AI->setName(*closure_iter);
        if(context->createVariable_llvm(*closure_iter, AI) == false) {
            generate_error(std::cerr, context, "ProcedureDecl::llvm_generate error: "
                    "cannot create local variable '" + *closure_iter + "'");
            std::abort();
        }//if
        ++closure_iter;
        ++AI;
    }//while

	return F;
}//llvm_generate(context)

}//namespace PL0

