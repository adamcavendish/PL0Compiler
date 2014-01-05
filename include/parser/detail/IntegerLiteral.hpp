#pragma once
// STL
#include <iostream>
#include <stdexcept>
#include <memory>
#include <utility>
#include <vector>
#include <limits>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>

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

	inline bool
	parse(std::shared_ptr<Tokenizer> toker) override;

PL0_PRIVATE: //member variables
	int m_value;
};//class IntegerLiteral

bool
IntegerLiteral::parse(std::shared_ptr<Tokenizer> toker) override {
	bool flag = true;

	try {
		m_value = std::stoi(toker->word());
	} catch(std::invalid_argument & e) {
		parse_error(toker, "Invalid Number format");
		flag = false;
	} catch(std::out_of_range & e) {
		parse_error(toker, "Number out of range. limit: ["
				+ std::to_string(std::numeric_limits<int>::min)
				+ ", "
				+ std::to_string(std::numeric_limits<int>::max)
				+ "]");
		flag = false;
	}//try-catch

	toker->next(); // eat the current number

	return flag;
}//parse(toker)

}//namespace PL0

