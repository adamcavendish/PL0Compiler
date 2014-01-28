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

class Statement : public ParserBase
{
PL0_PUBLIC:
	Statement() {}
	Statement(const Statement & rhs) = delete;
	Statement(Statement && rhs) :
		m_node(std::move(rhs.m_node))
	{}
	~Statement() {}

	Statement & operator=(const Statement & rhs) = delete;
	Statement & operator=(Statement && rhs) {
		if(this == &rhs)
			return (*this);

		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_node;
};//class Statement

}//namespace PL0

