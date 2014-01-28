#pragma once
// STL
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Context;

class IfStmt : public ParserBase
{
PL0_PUBLIC:
	IfStmt() {}
	IfStmt(const IfStmt & rhs) = delete;
	IfStmt(IfStmt && rhs) :
		m_condition_node(std::move(rhs.m_condition_node)),
		m_iftrue_node(std::move(rhs.m_iftrue_node))
	{}
	~IfStmt() {}

	IfStmt & operator=(const IfStmt & rhs) = delete;
	IfStmt & operator=(IfStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_condition_node = std::move(rhs.m_condition_node);
		m_iftrue_node = std::move(rhs.m_iftrue_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_condition_node;
	std::unique_ptr<ParserBase> m_iftrue_node;
};//class IfStmt

}//namespace PL0

