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

class Expression : public ParserBase
{
PL0_PUBLIC:
	Expression() {}
	Expression(const Expression & rhs) = delete;
	Expression(Expression && rhs) :
		m_node_first(std::move(rhs.m_node_first)),
		m_nodes(std::move(rhs.m_nodes))
	{}
	~Expression() {}

	Expression & operator=(const Expression & rhs) = delete;
	Expression & operator=(Expression && rhs) {
		if(this == &rhs)
			return (*this);

		m_node_first = std::move(rhs.m_node_first);
		m_nodes = std::move(rhs.m_nodes);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

PL0_PRIVATE:
	using Operator = char;

	std::unique_ptr<ParserBase> m_node_first;
	std::vector<std::pair<Operator, std::unique_ptr<ParserBase> > > m_nodes;
};//class Expression

}//namespace PL0

