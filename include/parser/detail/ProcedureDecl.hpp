#pragma once
// STL
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

class ProcedureDecl : public ParserBase
{
PL0_PUBLIC:
	ProcedureDecl() {}
	ProcedureDecl(const ProcedureDecl & rhs) = delete;
	ProcedureDecl(ProcedureDecl && rhs) :
		m_ident(std::move(rhs.m_ident))
	{}
	~ProcedureDecl() {}

	ProcedureDecl & operator=(const ProcedureDecl & rhs) = delete;
	ProcedureDecl & operator=(ProcedureDecl && rhs) {
		if(this == &rhs)
			return (*this);

		m_ident = std::move(rhs.m_ident);
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

PL0_PRIVATE:
	std::string m_ident;
};//class ProcedureDecl

}//namespace PL0

