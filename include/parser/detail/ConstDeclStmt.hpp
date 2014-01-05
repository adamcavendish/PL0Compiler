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

class ConstDeclStmt : public ParserBase
{
PL0_PUBLIC:
	ConstDeclStmt() {}
	ConstDeclStmt(const ConstDeclStmt & rhs) = delete;
	ConstDeclStmt(ConstDeclStmt && rhs) :
		m_node_vec(std::move(rhs.m_node_vec))
	{}
	~ConstDeclStmt() {}

	ConstDeclStmt & operator=(const ConstDeclStmt & rhs) = delete;
	ConstDeclStmt & operator=(ConstDeclStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_node_vec = std::move(rhs.m_node_vec);
		return (*this);
	}//move assignment

	bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE:
	std::vector<std::unique_ptr<ParserBase>> m_node_vec;
};//class ConstDeclStmt


}//namespace PL0

