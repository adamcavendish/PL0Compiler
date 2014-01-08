#include <parser/detail/IntegerLiteral.hpp>
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
#include <tokenizer/Tokenizer.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0
{

bool
IntegerLiteral::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	try {
		m_value = std::stoi(toker->word());
	} catch(std::invalid_argument & e) {
		parse_error(toker, "Invalid Number format");
		flag = false;
	} catch(std::out_of_range & e) {
		parse_error(toker, "Number out of range. limit: ["
				+ std::to_string(std::numeric_limits<int>::min())
				+ ", "
				+ std::to_string(std::numeric_limits<int>::max())
				+ "]");
		flag = false;
	}//try-catch

	toker->next(); // eat the current number

	return flag;
}//parse(os, toker)

void
IntegerLiteral::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "IntegerLiteral "
		<< this->position_str() << " '" << m_value << "'" << std::endl;
}//pretty_print(os, ident)

}//namespace PL0

