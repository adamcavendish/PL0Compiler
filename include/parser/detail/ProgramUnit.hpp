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

		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_node;
};//class ProgramUnit

}//namespace PL0

