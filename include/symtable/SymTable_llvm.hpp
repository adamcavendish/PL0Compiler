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
}

namespace PL0
{

class SymTable_llvm {
PL0_PUBLIC://functions
	llvm::AllocaInst *
	lookupVariable(const std::string & name) const;
PL0_PRIVATE://variables
	std::vector<
		std::unordered_map<std::string, llvm::AllocaInst *>
	> m_sym_arr;
};//class SymTable_llvm

}//namespace PL0

