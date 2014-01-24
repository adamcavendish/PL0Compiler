#pragma once

// STL
#include <iostream>
#include <memory>
#include <utility>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Context;

/**
 * @brief the parser automachine as a whole
 */
class Parser : public ParserBase
{
PL0_PUBLIC:
	Parser() {}
	Parser(const Parser & rhs) = delete;
	Parser(Parser && rhs) :
		m_genesis(std::move(rhs.m_genesis))
	{}
	~Parser() {}

	Parser & operator=(const Parser & rhs) = delete;
	Parser & operator=(Parser && rhs) {
		if(this == &rhs)
			return (*this);

		m_genesis = std::move(rhs.m_genesis);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_genesis;
};//class Parser

}//namespace PL0

