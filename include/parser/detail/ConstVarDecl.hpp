#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <preprocess.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class ConstVarDecl : public ParserBase {
PL0_PUBLIC:
	ConstVarDecl() {}
	ConstVarDecl(const ConstVarDecl & rhs) = delete;
	ConstVarDecl(ConstVarDecl && rhs) :
		m_ident(std::move(rhs.m_ident)),
		m_node(std::move(rhs.m_node))
	{}
	~ConstVarDecl() {}

	ConstVarDecl & operator=(const ConstVarDecl & rhs) = delete;
	ConstVarDecl & operator=(ConstVarDecl && rhs) {
		if(this == &rhs)
			return (*this);

		m_ident = std::move(rhs.m_ident);
		m_node = std::move(rhs.m_node);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	/**
	 * @brief m_ident stores the identifier
	 */
	std::string m_ident;

	/**
	 * @brief m_node stores the next abstract-syntax-tree node, @see README.md for the grammer
	 */
	std::unique_ptr<ParserBase> m_node;
};//class ConstVarDecl

}//namespace PL0


