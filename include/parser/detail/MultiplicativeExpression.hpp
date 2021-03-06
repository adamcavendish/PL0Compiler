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
#include <tokenizer/Tokenizer.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/UnaryExpression.hpp>

namespace PL0
{

class Context;

class MultiplicativeExpression : public ParserBase
{
PL0_PUBLIC:
	MultiplicativeExpression() {}
	MultiplicativeExpression(const MultiplicativeExpression & rhs) = delete;
	MultiplicativeExpression(MultiplicativeExpression && rhs) :
		m_node_first(std::move(rhs.m_node_first)),
		m_nodes(std::move(rhs.m_nodes))
	{}
	~MultiplicativeExpression() {}

	MultiplicativeExpression & operator=(const MultiplicativeExpression & rhs) = delete;
	MultiplicativeExpression & operator=(MultiplicativeExpression && rhs) {
		if(this == &rhs)
			return (*this);

		m_node_first = std::move(rhs.m_node_first);
		m_nodes = std::move(rhs.m_nodes);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	struct Operator {
		char m_op;
		std::pair<std::size_t, std::size_t> m_position;
	};//struct Operator

	std::unique_ptr<ParserBase> m_node_first;
	std::vector<std::pair<Operator, std::unique_ptr<ParserBase> > > m_nodes;
};//class MultiplicativeExpression

}//namespace PL0

