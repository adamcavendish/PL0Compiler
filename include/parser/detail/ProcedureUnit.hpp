#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_set>
#include <string>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Context;

class ProcedureUnit : public ParserBase
{
PL0_PUBLIC: // functions
	ProcedureUnit() {}
	ProcedureUnit(const ProcedureUnit & rhs) = delete;
	ProcedureUnit(ProcedureUnit && rhs) :
		m_proc_node(std::move(rhs.m_proc_node)),
		m_block(std::move(rhs.m_block))
	{}
	~ProcedureUnit() {}

	ProcedureUnit & operator=(const ProcedureUnit & rhs) = delete;
	ProcedureUnit & operator=(ProcedureUnit && rhs) {
		if(this == &rhs)
			return (*this);

		m_proc_node = std::move(rhs.m_proc_node);
		m_block = std::move(rhs.m_block);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE: // variables
	std::unique_ptr<ParserBase> m_proc_node;
	std::unique_ptr<ParserBase> m_block;
};//class ProcedureUnit

}//namespace PL0

