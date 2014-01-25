#pragma once

// STL
#include <memory>
#include <vector>
// PL0Compiler
#include <preprocess.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>

namespace PL0
{

class Tokenizer;
class SymTable;
class SymTable_llvm;

class Context {
PL0_PUBLIC://functions
	Context(std::shared_ptr<Tokenizer> toker) :
		m_toker(toker)
	{}

	/*
	 * Getters of the current class
	 */

	std::shared_ptr<Tokenizer>
	getTokenizer() const;

	std::shared_ptr<SymTable>
	getSymTable() const;

	std::shared_ptr<SymTable_llvm>
	getSymTable_llvm() const;

	std::shared_ptr<llvm::Module>
	getModule_llvm() const;

	std::shared_ptr<llvm::IRBuilder<>>
	getIRBuilder_llvm() const;

	std::shared_ptr<llvm::LLVMContext>
	getLLVMContext_llvm() const;

	/*
	 * Look-ups
	 */

	llvm::Function *
	lookupFunction_llvm(const std::string & name) const;

	llvm::Value *
	lookupVariable_llvm(const std::string & name) const;

	/*
	 * creates
	 */
	bool
	createVariable_llvm(const std::string & name, llvm::AllocaInst * inst);

PL0_PRIVATE://members
	std::shared_ptr<Tokenizer> m_toker;

	std::shared_ptr<SymTable> m_sym;
	std::shared_ptr<SymTable_llvm> m_sym_llvm;

	std::shared_ptr<llvm::LLVMContext> m_llvmcontext_llvm;
	std::shared_ptr<llvm::Module> m_module_llvm;

	std::shared_ptr<llvm::IRBuilder<>> m_irbuilder_llvm;
};//class Context

}//namespace PL0

