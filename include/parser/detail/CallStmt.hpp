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

class CallStmt : public ParserBase
{
PL0_PUBLIC:
	CallStmt() {}
	CallStmt(const CallStmt & rhs) = delete;
	CallStmt(CallStmt && rhs) :
		m_node(std::move(rhs.m_node))
	{}
	~CallStmt() {}

	CallStmt & operator=(const CallStmt & rhs) = delete;
	CallStmt & operator=(CallStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_node;
};//class CallStmt

}//namespace PL0

