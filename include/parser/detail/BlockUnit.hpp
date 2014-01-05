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

class BlockUnit : public ParserBase
{
PL0_PUBLIC:
	BlockUnit() {}
	BlockUnit(const BlockUnit & rhs) = delete;
	BlockUnit(BlockUnit && rhs) :
		m_const_decl_stmt(std::move(rhs.m_const_decl_stmt)),
		m_var_decl_stmt(std::move(rhs.m_var_decl_stmt))
	{}
	~BlockUnit() {}

	BlockUnit & operator=(const BlockUnit & rhs) = delete;
	BlockUnit & operator=(BlockUnit && rhs) {
		if(this == &rhs)
			return (*this);

		m_const_decl_stmt = std::move(rhs.m_const_decl_stmt);
		m_var_decl_stmt = std::move(rhs.m_var_decl_stmt);
		return (*this);
	}//move assignment

	bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_const_decl_stmt;
	std::unique_ptr<ParserBase> m_var_decl_stmt;
};//class BlockUnit


}//namespace PL0

