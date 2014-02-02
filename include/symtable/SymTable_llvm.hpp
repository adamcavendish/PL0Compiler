#pragma once

// STL
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
// PL0Compiler
#include <preprocess.hpp>

namespace llvm  {
	class AllocaInst;
	class Value;
	class Constant;
}

namespace PL0
{

class SymTable_llvm {
PL0_PUBLIC://functions
	/**
	 * @brief	Create a new local sym table for look up.
	 *			Usually used at entering a BlockUnit/Function.
	 */
	void
	createLocalSymTable();

	/**
	 * @brief	Drop the current local sym table.
	 *			Usually used at exiting a BlockUnit/Funciton.
	 */
	void
	dropLocalSymTable();
	
	/**
	 * @brief Lookup a local variable (non-constant)
     * @return whether it is found and the corresponding AllocaInst *
	 */
    std::pair<bool, llvm::AllocaInst *>
	lookupVariable_local(const std::string & name) const;

    /**
     * @brief Lookup a local constant
     * @return whether it is found and the corresponding Constant *
     */
    std::pair<bool, llvm::Constant *>
    lookupConstant_local(const std::string & name) const;

    /**
     * @brief Lookup a parent variable (non-constant)
     * @return whether it is found and the corresponding AllocaInst *
     */
    std::pair<bool, llvm::AllocaInst *>
    lookupVariable_parent(const std::string & name) const;

    /**
     * @brief Lookup a parent constant
     * @return whether it is found and the corresponding Constant *
     */
    std::pair<bool, llvm::Constant *>
    lookupConstant_parent(const std::string & name) const;

	/**
	 * @brief Create a variable (non-constant)
     * @return true if succeeded, false (redefinition) if failed.
	 */
	bool
	createVariable(const std::string & name, llvm::AllocaInst * inst);

	/**
	 * @brief Create a Constant
     * @return true if succeeded, false (redefinition) if failed.
	 */
	bool
	createConstant(const std::string & name, llvm::Constant * constant);

	/**
	 * @brief Set a variable's corresponding AllocaInst to `inst` (non-constant)
     * @return true if succeeded, false (no definition) if failed
	 */
	bool
	setVariable(const std::string & name, llvm::AllocaInst * inst);

	/**
	 * @brief Set a Constant's corresponding Constant to `constant`
     * @return true if succeeded, false (no definition) if failed
	 */
	bool
	setConstant(const std::string & name, llvm::Constant * constant);

PL0_PRIVATE://variables
	std::vector<
		std::unordered_map<std::string, llvm::AllocaInst *>
	> m_sym_arr;

	std::vector<
		std::unordered_map<std::string, llvm::Constant *>
	> m_constsym_arr;
};//class SymTable_llvm

}//namespace PL0

