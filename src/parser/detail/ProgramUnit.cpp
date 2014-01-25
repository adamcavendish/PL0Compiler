#include <parser/detail/ProgramUnit.hpp>
// STL
#include <memory>
#include <iostream>
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
#include <parser/detail/BlockUnit.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace PL0
{

bool
ProgramUnit::parse(std::ostream & os, std::shared_ptr<Context> context) {
	m_position = context->getTokenizer()->position();
	bool flag = true;

	auto block = auc::make_unique<BlockUnit>();

	if(!block->parse(os, context))
		flag = false;
	m_node = std::move(block);

	if(flag == true) {
		if(context->getTokenizer()->token() == Token::tk_period) {
			context->getTokenizer()->next(); // eat '.' token
		} else {
			parse_error(os, context, "A program needs to be ended with a '.'");
			flag = false;
		}//if-else
	}//if

	return flag;
}//parse(os, context)

void
ProgramUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProgramUnit " << this->position_str() << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
ProgramUnit::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::FunctionType * func_type = llvm::FunctionType::get(
			llvm::Type::getVoidTy(*context->getLLVMContext_llvm()), false);
	if(func_type == nullptr) {
		generate_error(std::cerr, context,
				"ProgramUnit::llvm_generate::FunctionType generate error");
		std::abort();
	}//if

	llvm::Function * func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage,
			"__global_main_entry__", context->getModule_llvm().get());
	if(func == nullptr) {
		generate_error(std::cerr, context, "ProgramUnit::llvm_generate::Function create error");
		std::abort();
	}//if

	llvm::BasicBlock * bb = llvm::BasicBlock::Create(*context->getLLVMContext_llvm(),
			"BlockUnitEntry", func);
	if(bb == nullptr) {
		generate_error(std::cerr, context,
				"ProgramUnit::llvm_generate::BasicBlock generate error");
		std::abort();
	}//if

	llvm::Value * blockgen = m_node->llvm_generate(context);
	if(blockgen == nullptr) {
		generate_error(std::cerr, context,
				"ProgramUnit->BlockUnit::llvm_generate error");
		flag = false;
		// do not abort for tracing back the error.
	}//if

	if(flag == true)
		return func;
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

