#pragma once
// STL
#include <iostream>
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>

namespace PL0
{

class IntegerLiteral;

class VarDecl : public ParserBase {
PL0_PUBLIC:
	VarDecl() {}
	VarDecl(const VarDecl & rhs) = delete;
	VarDecl(VarDecl && rhs) :
		m_ident(std::move(rhs.m_ident))
	{}
	~VarDecl() {}

	VarDecl & operator=(const VarDecl & rhs) = delete;
	VarDecl & operator=(VarDecl && rhs) {
		if(this == &rhs)
			return (*this);

		m_ident = std::move(rhs.m_ident);
		return (*this);
	}//move assignment

	inline bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE:
	/**
	 * @brief m_ident stores the identifier
	 */
	std::string m_ident;
};//class VarDecl

bool
VarDecl::parse(std::shared_ptr<Tokenizer> toker) {
	m_ident = toker->word();
	toker->next(); // eat the current identifier
	return true;
}//parse(toker)

}//namespace PL0

