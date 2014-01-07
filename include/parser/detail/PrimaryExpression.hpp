#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <string>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Tokenizer;

class PrimaryExpression : public ParserBase
{
PL0_PUBLIC: // functions
	PrimaryExpression() {}
	PrimaryExpression(const PrimaryExpression & rhs) = delete;
	PrimaryExpression(PrimaryExpression && rhs) :
		m_node(std::move(rhs.m_node))
	{}
	~PrimaryExpression() {}

	PrimaryExpression & operator=(const PrimaryExpression & rhs) = delete;
	PrimaryExpression & operator=(PrimaryExpression && rhs) {
		if(this == &rhs)
			return (*this);

		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

PL0_PRIVATE: // variables
	std::unique_ptr<ParserBase> m_node;
};//class PrimaryExpression

}//namespace PL0

