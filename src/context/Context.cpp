#include <context/Context.hpp>
// STL
#include <memory>
// C-STL
#include <cassert>
// PL0Compiler
#include <preprocess.hpp>
#include <symtable/SymTable_llvm.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace PL0 {

std::shared_ptr<Tokenizer>
Context::getTokenizer() const {
	assert(m_toker != nullptr && "Tring to use Tokenizer while it is null");
	return m_toker;
}//getTokenizer()

std::shared_ptr<SymTable>
Context::getSymTable() const {
	assert(m_sym != nullptr && "Tring to use SymTable while it is null");
	return m_sym;
}//getSymTable()

std::shared_ptr<SymTable_llvm>
Context::getSymTable_llvm() const {
	assert(m_sym_llvm != nullptr && "Tring to use llvm SymTable while it is null");
	return m_sym_llvm;
}//getSymTable_llvm()

std::shared_ptr<llvm::Module>
Context::getModule_llvm() const {
	assert(m_module_llvm != nullptr && "Tring to use llvm Module while it is null");
	return m_module_llvm;
}//getModule_llvm()

std::shared_ptr<llvm::IRBuilder<>>
Context::getIRBuilder_llvm() const {
	assert(m_irbuilder_llvm != nullptr && "Tring to use llvm IRBuilder while it is null");
	return m_irbuilder_llvm;
}//getIRBuilder_llvm()

llvm::Function *
Context::lookupFunction_llvm(const std::string & name) const {
	return m_module_llvm->getFunction(name);
}//lookupFunction_llvm(name)

llvm::AllocaInst *
Context::lookupVariable_llvm(const std::string & name) const {
	return this->getSymTable_llvm()->lookupVariable(name);
}//lookupVariable_llvm(name)

}//namespace PL0

