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

std::pair<bool, llvm::AllocaInst *>
SymTable_llvm::lookupVariable_local(const std::string & name) const {
    if(m_sym_arr.empty())
        return std::make_pair(false, nullptr);

    auto & local_sym = m_sym_arr.back();
    auto ret = local_sym.find(name);
    if(ret == local_sym.end())
        return std::make_pair(false, nullptr);
    
    return std::make_pair(true, ret->second);
}//lookupVariable_local(name)

std::pair<bool, llvm::AllocaInst *>
SymTable_llvm::lookupVariable_parent(const std::string & name) const {
    if(m_sym_arr.empty())
        return std::make_pair(false, nullptr);

    // sym table iterator
    auto iter = m_sym_arr.end();
    --iter; //skip the local sym table (at the back)
    auto iter_end = m_sym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end())
            return std::make_pair(true, ret->second);
    } while(iter != iter_end);

    return std::make_pair(false, nullptr);
}//lookupVariable_parent(name)

std::pair<bool, llvm::Constant *>
SymTable_llvm::lookupConstant_local(const std::string & name) const {
    if(m_constsym_arr.empty())
        return std::make_pair(false, nullptr);

    auto & local_const = m_constsym_arr.back();
    auto ret = local_const.find(name);
    if(ret == local_const.end())
        return std::make_pair(false, nullptr);
    
    return std::make_pair(true, ret->second);
}//lookupConstant_local(name)

std::pair<bool, llvm::Constant *>
SymTable_llvm::lookupConstant_parent(const std::string & name) const {
    if(m_constsym_arr.empty())
        return std::make_pair(false, nullptr);

    // sym table iterator
    auto iter = m_constsym_arr.end();
    --iter; //skip the local sym table (at the back)
    auto iter_end = m_constsym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end())
            return std::make_pair(true, ret->second);
    } while(iter != iter_end);

    return std::make_pair(false, nullptr);
}//lookupVariable_parent(name)

bool
SymTable_llvm::createVariable(const std::string & name, llvm::AllocaInst * inst) {
    if(this->lookupVariable_local(name).first == true)
        return false;

	auto ret = m_sym_arr.back().insert(std::make_pair(name, inst));
	return ret.second;
}//createVariable(name, inst)

bool
SymTable_llvm::createConstant(const std::string & name, llvm::Constant * constant) {
    if(this->lookupConstant_local(name).first == true)
        return false;

	auto ret = m_constsym_arr.back().insert(std::make_pair(name, constant));
	return ret.second;
}//createConstant(name, constant)

bool
SymTable_llvm::setVariable(const std::string & name, llvm::AllocaInst * inst) {
    if(m_sym_arr.empty())
        return false;

    // sym table iterator
    auto iter = m_sym_arr.end();
    auto iter_end = m_sym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end()) {
            ret->second = inst;
            return true;
        }//if
    } while(iter != iter_end);

    return false;
}//setVariable(name, inst)

bool
SymTable_llvm::setConstant(const std::string & name, llvm::Constant * constant) {
    if(m_constsym_arr.empty())
        return false;

    // sym table iterator
    auto iter = m_constsym_arr.end();
    auto iter_end = m_constsym_arr.begin();
    do {
        --iter;
        auto ret = iter->find(name);
        if(ret != iter->end()) {
            ret->second =constant;
            return true;
        }//if
    } while(iter != iter_end);

    return false;
}//setConstant(name, inst)

}//namespace PL0

