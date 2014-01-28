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

namespace PL0 {

class Context;

class IntegerLiteral : public ParserBase {
PL0_PUBLIC: //member functions
	IntegerLiteral() {}
	IntegerLiteral(const IntegerLiteral & rhs) = delete;
	IntegerLiteral(IntegerLiteral && rhs) :
		m_value(rhs.m_value)
	{}
	~IntegerLiteral() {}

	IntegerLiteral & operator=(const IntegerLiteral & rhs) = delete;
	IntegerLiteral & operator=(IntegerLiteral && rhs) {
		if(this == &rhs)
			return (*this);

		m_value = rhs.m_value;
		return (*this);
	}//move assignment

	bool
	parse(std::ostream & os, std::shared_ptr<Context> context) override;

	void
	pretty_print(std::ostream & os, std::size_t indent) const override;

	llvm::Value *
	llvm_generate(std::shared_ptr<Context> context) const override;

PL0_PRIVATE: //member variables
	int m_value;
};//class IntegerLiteral

}//namespace PL0

