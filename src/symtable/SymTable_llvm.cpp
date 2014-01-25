#include <symtable/SymTable_llvm.hpp>
// STL
#include <iostream>
#include <memory>
#include <map>
#include <utility>
// PL0Compiler
#include <preprocess.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace PL0
{
void
SymTable_llvm::createLocalSymTable() {
	m_sym_arr.push_back(decltype(m_sym_arr)::value_type());
	m_constsym_arr.push_back(decltype(m_constsym_arr)::value_type());
}//createLocalSymTable()

void
SymTable_llvm::dropLocalSymTable() {
	m_sym_arr.pop_back();
	m_constsym_arr.pop_back();
}//dropLocalSymTable()

llvm::Value *
SymTable_llvm::lookupVariable(const std::string & name) const {
	auto & last_localsym_table_ref = m_sym_arr.back();
	auto ret = last_localsym_table_ref.find(name);
	if(ret == last_localsym_table_ref.end())
		return nullptr;
	return (ret->second);
}//lookupVariable(name)

bool
SymTable_llvm::createVariable(const std::string & name, llvm::AllocaInst * inst) {
	auto ret = m_sym_arr.back().insert(std::make_pair(name, inst));
	return ret.second;
}//createVariable(name, inst)

bool
SymTable_llvm::createConstant(const std::string & name, llvm::Constant * constant) {
	auto ret = m_constsym_arr.back().insert(std::make_pair(name, constant));
	return ret.second;
}//createConstant(name, constant)

}//namespace PL0

