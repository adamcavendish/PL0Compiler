#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class Tokenizer;
class Expression;

class BlockUnit : public ParserBase
{
PL0_PUBLIC:
	BlockUnit() {}
	BlockUnit(const BlockUnit & rhs) = delete;
	BlockUnit(BlockUnit && rhs) :
		m_const_decl_stmt(std::move(rhs.m_const_decl_stmt)),
		m_var_decl_stmt(std::move(rhs.m_var_decl_stmt)),
		m_expr(std::move(rhs.m_expr))
	{}
	~BlockUnit() {}

	BlockUnit & operator=(const BlockUnit & rhs) = delete;
	BlockUnit & operator=(BlockUnit && rhs) {
		if(this == &rhs)
			return (*this);

		m_const_decl_stmt = std::move(rhs.m_const_decl_stmt);
		m_var_decl_stmt = std::move(rhs.m_var_decl_stmt);
		m_expr = std::move(rhs.m_expr);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

PL0_PRIVATE:
	std::unique_ptr<ParserBase> m_const_decl_stmt;
	std::unique_ptr<ParserBase> m_var_decl_stmt;

	// @TODO grammar not complete
	std::unique_ptr<ParserBase> m_expr;
};//class BlockUnit

}//namespace PL0

