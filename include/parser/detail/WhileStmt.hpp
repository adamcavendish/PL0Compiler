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

class Tokenizer;

class WhileStmt : public ParserBase
{
PL0_PUBLIC:
	WhileStmt() {}
	WhileStmt(const WhileStmt & rhs) = delete;
	WhileStmt(WhileStmt && rhs) :
		m_condition_node(std::move(rhs.m_condition_node)),
		m_stmt_node(std::move(rhs.m_stmt_node))
	{}
	~WhileStmt() {}

	WhileStmt & operator=(const WhileStmt & rhs) = delete;
	WhileStmt & operator=(WhileStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_condition_node = std::move(rhs.m_condition_node);
		m_stmt_node = std::move(rhs.m_stmt_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_condition_node;
	std::unique_ptr<ParserBase> m_stmt_node;
};//class WhileStmt

}//namespace PL0

