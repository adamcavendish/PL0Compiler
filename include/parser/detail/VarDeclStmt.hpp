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

class VarDeclStmt : public ParserBase
{
PL0_PUBLIC:
	VarDeclStmt() {}
	VarDeclStmt(const VarDeclStmt & rhs) = delete;
	VarDeclStmt(VarDeclStmt && rhs) :
		m_node_vec(std::move(rhs.m_node_vec))
	{}
	~VarDeclStmt() {}

	VarDeclStmt & operator=(const VarDeclStmt & rhs) = delete;
	VarDeclStmt & operator=(VarDeclStmt && rhs) {
		if(this == &rhs)
			return (*this);

		m_node_vec = std::move(rhs.m_node_vec);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::vector<std::unique_ptr<ParserBase> > m_node_vec;
};//class VarDeclStmt

}//namespace PL0

