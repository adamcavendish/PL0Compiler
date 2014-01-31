#include <parser/detail/ProcedureUnit.hpp>
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
#include <parser/detail/ProcedureDecl.hpp>
#include <parser/detail/BlockUnit.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>

namespace PL0
{

bool
ProcedureUnit::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	auto proc_decl = auc::make_unique<ProcedureDecl>();
	if(!proc_decl->parse(os, context))
		flag = false;
	m_proc_node = std::move(proc_decl);

	auto block = auc::make_unique<BlockUnit>();
	if(!block->parse(os, context))
		flag = false;
	m_block = std::move(block);

	if(flag == true) {
		if(toker->token() != Token::tk_semicolon) {
			flag = false;
			parse_error(os, context, "A ';' expected after a whole procedure definition.");
		} else {
			toker->next(); // eat the current ';' token
		}//if-else
	}//if

	return flag;
}//parse(os, context)

void
ProcedureUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProcedureUnit " << this->position_str() << std::endl;

	if(m_proc_node)
		m_proc_node->pretty_print(os, indent+1);
	if(m_block)
		m_block->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
ProcedureUnit::llvm_generate(std::shared_ptr<Context> context) const {
    bool flag = true;
	llvm::Function * procedure = (llvm::Function *)(m_proc_node->llvm_generate(context));
	if(procedure == nullptr) {
		// @FIXME
		generate_error(std::cerr, context, "Function Redefinition");
        flag = false;
	}//if

	llvm::BasicBlock * BB = llvm::BasicBlock::Create(
			*(context->getLLVMContext_llvm()), "ProcedureEntry", procedure);
	if(BB == nullptr) {
		generate_error(std::cerr, context, "ProcedureUnit::llvm_generate BasicBlock Creation Error");
		std::abort();
	}//if
	context->getIRBuilder_llvm()->SetInsertPoint(BB);

	llvm::Value * block = m_block->llvm_generate(context);
	if(block == nullptr) {
		generate_error(std::cerr, context, "ProcedureUnit->BlockUnit llvm_generate error");
        flag = false;
	}//if

	context->getIRBuilder_llvm()->SetInsertPoint(BB);
	// Finish off the function.
	context->getIRBuilder_llvm()->CreateRetVoid();
	// Validate the generated code, checking for consistency.
	llvm::verifyFunction(*procedure);

    if(flag == true) {
        return llvm::Constant::getNullValue(
                llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())));
    }//if
    return nullptr;
} //llvm_generate(context)

}//namespace PL0

