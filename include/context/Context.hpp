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
	Context(
			std::shared_ptr<Tokenizer> toker,
			std::shared_ptr<SymTable> symtable,
			std::shared_ptr<SymTable_llvm> symtable_llvm,
			std::shared_ptr<llvm::LLVMContext> context_llvm,
			std::shared_ptr<llvm::Module> module_llvm,
			std::shared_ptr<llvm::IRBuilder<>> builder_llvm) :
		m_toker(toker),
		m_sym(symtable),
		m_sym_llvm(symtable_llvm),
		m_llvmcontext_llvm(context_llvm),
		m_module_llvm(module_llvm),
		m_irbuilder_llvm(builder_llvm)
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

    std::vector<std::string> &
    getClosure()
    { return m_closure.back(); }

	/*
	 * Look-ups
	 */

	llvm::Function *
	lookupFunction_llvm(const std::string & name) const;

    std::pair<bool, llvm::AllocaInst *>
	lookupVariable_local_llvm(const std::string & name) const;

    std::pair<bool, llvm::Constant *>
    lookupConstant_local_llvm(const std::string & name) const;

    std::pair<bool, llvm::AllocaInst *>
	lookupVariable_parent_llvm(const std::string & name) const;

    std::pair<bool, llvm::Constant *>
    lookupConstant_parent_llvm(const std::string & name) const;

	/*
	 * creates
	 */

    void
    createLocalSymTable_llvm();

	bool
	createVariable_llvm(const std::string & name, llvm::AllocaInst * inst);

    bool
    createConstant_llvm(const std::string & name, llvm::Constant * constant);

    void
    createClosure()
    { m_closure.push_back(decltype(m_closure)::value_type()); }
    
    /**
     * Destroyers
     */
	void
	dropLocalSymTable_llvm();

    void
    dropClosure()
    { m_closure.pop_back(); }

    /**
     * Modifiers
     */
    bool
    setVariable_llvm(const std::string & name, llvm::AllocaInst * inst);

    bool
    setConstant_llvm(const std::string & name, llvm::Constant * constant);

PL0_PRIVATE://members
	std::shared_ptr<Tokenizer> m_toker;

	std::shared_ptr<SymTable> m_sym;
    std::vector<std::vector<std::string>> m_closure;

	std::shared_ptr<SymTable_llvm> m_sym_llvm;
	std::shared_ptr<llvm::LLVMContext> m_llvmcontext_llvm;
	std::shared_ptr<llvm::Module> m_module_llvm;
	std::shared_ptr<llvm::IRBuilder<>> m_irbuilder_llvm;
};//class Context

}//namespace PL0

