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

class ProgramUnit : public ParserBase
{
PL0_PUBLIC:
	ProgramUnit() {}
	ProgramUnit(const ProgramUnit & rhs) = delete;
	ProgramUnit(ProgramUnit && rhs) :
		m_node(std::move(rhs.m_node))
	{}
	~ProgramUnit() {}

	ProgramUnit & operator=(const ProgramUnit & rhs) = delete;
	ProgramUnit & operator=(ProgramUnit && rhs) {
		if(this == &rhs)
			return (*this);

		m_node = std::move(rhs.m_node)
		return (*this);
	}//move assignment

	inline bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_node;
};//class ProgramUnit

bool
ProgramUnit::parse(std::shared_ptr<Tokenizer> toker) override {
	bool flag = true;

	auto block = auc::make_unique<BlockUnit>();

	if(block.parse()) {
		m_node = block;
	} else {
		flag = false;
	}//if-else

	if(flag = true && toker->token() == Token::tk_period) {
		toker->next(); // eat '.' token
	} else {
		parse_error(toker, "A program needs to be ended with a '.'");
		flag = false;
	}//if-else

	return flag;
}//parse(toker)

}//namespace PL0

