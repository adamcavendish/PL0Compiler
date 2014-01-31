#include <parser/detail/VarDecl.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/IntegerLiteral.hpp>

namespace PL0
{

bool
VarDecl::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auc_UNUSED(os);

	m_position = context->getTokenizer()->position();

	m_ident = context->getTokenizer()->word();
	context->getTokenizer()->next(); // eat the current identifier

	return true;
}//parse(os, context)

void
VarDecl::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "VarDecl "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

llvm::Value *
VarDecl::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::AllocaInst * ret = context->getIRBuilder_llvm()->CreateAlloca(
			llvm::Type::getInt32Ty(*context->getLLVMContext_llvm()),
            nullptr,
            m_ident);
	if(ret == nullptr) {
		generate_error(std::cerr, context,
				"VarDecl::llvm_generate Stack Allocation Instruction create error");
		flag = false;
	}//if

	if(context->createVariable_llvm(m_ident, ret) == false) {
        generate_error(std::cerr, context,
                "Redefinition of variable: " + m_ident);
        flag = false;
    }//if

	if(flag == false) {
        ret->removeFromParent();
		return nullptr;
    }//if
	return ret;
}//llvm_generate(context)

}//namespace PL0

