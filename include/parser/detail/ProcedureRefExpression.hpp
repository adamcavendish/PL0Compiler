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

class ProcedureRefExpression : public ParserBase
{
PL0_PUBLIC: // functions
	ProcedureRefExpression() {}
	ProcedureRefExpression(const ProcedureRefExpression & rhs) = delete;
	ProcedureRefExpression(ProcedureRefExpression && rhs) :
		m_ident(std::move(rhs.m_ident))
	{}
	~ProcedureRefExpression() {}

	ProcedureRefExpression & operator=(const ProcedureRefExpression & rhs) = delete;
	ProcedureRefExpression & operator=(ProcedureRefExpression && rhs) {
		if(this == &rhs)
			return (*this);

		m_ident = std::move(rhs.m_ident);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE: // variables
	std::string m_ident;
};//class ProcedureRefExpression

}//namespace PL0

