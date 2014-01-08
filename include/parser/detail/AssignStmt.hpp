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

class AssignStmt : public ParserBase
{
PL0_PUBLIC:
	AssignStmt() {}
	AssignStmt(const AssignStmt & rhs) = delete;
	AssignStmt(AssignStmt && rhs) :
		m_assign_left(std::move(rhs.m_assign_left)),
		m_assign_right(std::move(rhs.m_assign_right))
	{}
	~AssignStmt() {}

	AssignStmt & operator=(const AssignStmt & rhs) = delete;
	AssignStmt & operator=(AssignStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_assign_left = std::move(rhs.m_assign_left);
		m_assign_right = std::move(rhs.m_assign_right);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_assign_left;
	std::unique_ptr<ParserBase> m_assign_right;
};//class AssignStmt

}//namespace PL0

