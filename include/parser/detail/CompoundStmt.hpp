#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Tokenizer;

class CompoundStmt : public ParserBase
{
PL0_PUBLIC: // functions
	CompoundStmt() {}
	CompoundStmt(const CompoundStmt & rhs) = delete;
	CompoundStmt(CompoundStmt && rhs) :
		m_nodes(std::move(rhs.m_nodes))
	{}
	~CompoundStmt() {}

	CompoundStmt & operator=(const CompoundStmt & rhs) = delete;
	CompoundStmt & operator=(CompoundStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_nodes = std::move(rhs.m_nodes);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE: // variables
	std::vector<std::unique_ptr<ParserBase> > m_nodes;
};//class CompoundStmt

}//namespace PL0

