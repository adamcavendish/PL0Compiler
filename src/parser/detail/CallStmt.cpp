#include <parser/detail/CallStmt.hpp>
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
#include <parser/detail/ProcedureRefExpression.hpp>

namespace PL0
{

bool
CallStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	m_position = context->getTokenizer()->position();
	bool flag = true;

	context->getTokenizer()->next(); // eat the 'call' token

	auto func_ref = auc::make_unique<ProcedureRefExpression>();
	if(!func_ref->parse(os, context))
		flag = false;
	m_node = std::move(func_ref);

	return flag;
}//parse(os, context)

void
CallStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "CallStmt " << this->position_str() << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
CallStmt::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::Value * func = m_node->llvm_generate(context);
	if(func == nullptr) {
		generate_error(std::cerr, context, "CallStmt->ProcedureRefExpression llvm_generate error");
		flag = false;
	}//if

    // trying to get function closure
    auto pclosure_ref = [&]() -> std::unordered_set<std::string> * {
        std::string function_name = func->getName();
        auto finditer = context->getFunctionClosureMap()->find(function_name);
        if(finditer != context->getFunctionClosureMap()->end()) {
            return &(finditer->second);
        } else {
            generate_error(std::cerr, context, "CallStmt trying to ref a function "
                    "does not exist in closure map: " + function_name);
            flag = false;
            return nullptr;
        }//if-else
        return nullptr;
    }();

#if 1
    std::cerr << "CallStmt::function closure: " << std::string(func->getName()) << std::endl;
#endif

    // get closure elements
    auto args = [&]() -> std::vector<llvm::Value *> {
        std::vector<llvm::Value *> ret;

        for(auto && i : *pclosure_ref) {
#if 1
            std::cerr << "\t" << i << std::endl;
#endif
            auto varret = context->lookupVariable_local_llvm(i);
            auto constret = context->lookupConstant_local_llvm(i);

            if(varret.first != true) {
                ret.push_back(varret.second);
                continue;
            }//if

            if(constret.first == true) {
                ret.push_back(constret.second);
                continue;
            }//if

            generate_error(std::cerr, context, "CallStmt::llvm_generate trying to closure"
                    " element not found in local symtable '" + i + "'");
            std::abort();
        }//for
        return ret;
    }();

    // if `func` returns void you cannot assign a name to the ret (because there's no ret ._. ).
	llvm::CallInst * ret = context->getIRBuilder_llvm()->CreateCall(func, args);
	if(ret == nullptr) {
		generate_error(std::cerr, context, "CallStmt::llvm_generate Call Instruction Create error");
		std::abort();
	}//if

	if(flag == true)
		return ret;
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

