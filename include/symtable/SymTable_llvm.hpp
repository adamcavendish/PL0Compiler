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
	 * @brief Lookup a variable, either constant or variable
	 */
	llvm::Value *
	lookupVariable(const std::string & name) const;

	/**
	 * @brief Create a variable (non-constant)
	 */
	bool
	createVariable(const std::string & name, llvm::AllocaInst * inst);

	/**
	 * @brief Create a Constant
	 */
	bool
	createConstant(const std::string & name, llvm::Constant * constant);

PL0_PRIVATE://variables
	std::vector<
		std::unordered_map<std::string, llvm::AllocaInst *>
	> m_sym_arr;

	std::vector<
		std::unordered_map<std::string, llvm::Constant *>
	> m_constsym_arr;
};//class SymTable_llvm

}//namespace PL0

