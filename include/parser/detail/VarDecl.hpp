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

class Context;
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

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE:
	/**
	 * @brief m_ident stores the identifier
	 */
	std::string m_ident;
};//class VarDecl

}//namespace PL0

