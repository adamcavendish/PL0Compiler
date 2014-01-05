#pragma once

// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0
{

class Tokenizer;

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

	inline bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_genesis;
};//class Parser

bool
Parser::parse(std::shared_ptr<Tokenizer> toker) override {
	auto prog = auc::make_unique<ProgramUnit>();

	if(prog->parse(toker)) {
		m_genesis = prog;
	} else {
		return false;
	}//if-else
	return true;
}//parse(toker)

}//namespace PL0

