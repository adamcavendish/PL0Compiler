#include <parser/detail/FunctionRefExpression.hpp>
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
#include <tokenizer/Tokenizer.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0
{

bool
FunctionRefExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();

	m_ident = toker->word();
	toker->next(); // eat current function identifier
	return true;
}//parse(os, toker)

void
FunctionRefExpression::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "FunctionRefExpression "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

}//namespace PL0

