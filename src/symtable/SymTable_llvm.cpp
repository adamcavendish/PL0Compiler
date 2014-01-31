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

llvm::AllocaInst *
SymTable_llvm::lookupVariable(const std::string & name) const {
    if(m_sym_arr.empty())
        return nullptr;

    // sym table iterator
    auto iter = m_sym_arr.end();
    auto iter_end = m_sym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end())
            return (ret->second);
    } while(iter != iter_end);

    return nullptr;
}//lookupVariable(name)

llvm::Constant *
SymTable_llvm::lookupConstant(const std::string & name) const {
    if(m_constsym_arr.empty())
        return nullptr;

    // sym table iterator
    auto iter = m_constsym_arr.end();
    auto iter_end = m_constsym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end())
            return (ret->second);
    } while(iter != iter_end);

    return nullptr;
}//lookupConstant(name)

bool
SymTable_llvm::createVariable(const std::string & name, llvm::AllocaInst * inst) {
    if(this->lookupConstant(name) != nullptr)
        return false;

	auto ret = m_sym_arr.back().insert(std::make_pair(name, inst));
	return ret.second;
}//createVariable(name, inst)

bool
SymTable_llvm::createConstant(const std::string & name, llvm::Constant * constant) {
    if(this->lookupVariable(name) != nullptr)
        return false;

	auto ret = m_constsym_arr.back().insert(std::make_pair(name, constant));
	return ret.second;
}//createConstant(name, constant)

}//namespace PL0

