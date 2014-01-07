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
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) override;

	void
	pretty_print(std::ostream & os, std::size_t ident) const override;

PL0_PRIVATE: //member variables
	int m_value;
};//class IntegerLiteral

}//namespace PL0

