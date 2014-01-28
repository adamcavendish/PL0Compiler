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

class Context;

class FunctionRefExpression : public ParserBase
{
PL0_PUBLIC: // functions
	FunctionRefExpression() {}
	FunctionRefExpression(const FunctionRefExpression & rhs) = delete;
	FunctionRefExpression(FunctionRefExpression && rhs) :
		m_ident(std::move(rhs.m_ident))
	{}
	~FunctionRefExpression() {}

	FunctionRefExpression & operator=(const FunctionRefExpression & rhs) = delete;
	FunctionRefExpression & operator=(FunctionRefExpression && rhs) {
		if(this == &rhs)
			return (*this);

		m_ident = std::move(rhs.m_ident);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE: // variables
	std::string m_ident;
};//class FunctionRefExpression

}//namespace PL0

