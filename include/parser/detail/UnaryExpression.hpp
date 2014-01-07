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

class UnaryExpression : public ParserBase
{
PL0_PUBLIC:
	UnaryExpression() {}
	UnaryExpression(const UnaryExpression & rhs) = delete;
	UnaryExpression(UnaryExpression && rhs) :
		m_unary_op(rhs.m_unary_op),
		m_node(std::move(rhs.m_node))
	{}
	~UnaryExpression() {}

	UnaryExpression & operator=(const UnaryExpression & rhs) = delete;
	UnaryExpression & operator=(UnaryExpression && rhs) {
		if(this == &rhs)
			return (*this);

		m_unary_op = rhs.m_unary_op;
		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

PL0_PRIVATE:
	char m_unary_op;
	std::unique_ptr<ParserBase> m_node;
};//class UnaryExpression

}//namespace PL0

