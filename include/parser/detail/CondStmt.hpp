#pragma once
// STL
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Context;

class CondStmt : public ParserBase
{
PL0_PUBLIC:
	CondStmt() {}
	CondStmt(const CondStmt & rhs) = delete;
	CondStmt(CondStmt && rhs) :
		m_condition_op(rhs.m_condition_op),
		m_expr_node1(std::move(rhs.m_expr_node1)),
		m_expr_node2(std::move(rhs.m_expr_node2))
	{}
	~CondStmt() {}

	CondStmt & operator=(const CondStmt & rhs) = delete;
	CondStmt & operator=(CondStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_condition_op = rhs.m_condition_op;
		m_expr_node1 = std::move(rhs.m_expr_node1);
		m_expr_node2 = std::move(rhs.m_expr_node2);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	Token m_condition_op;
	std::unique_ptr<ParserBase> m_expr_node1;
	std::unique_ptr<ParserBase> m_expr_node2;
};//class CondStmt

}//namespace PL0

