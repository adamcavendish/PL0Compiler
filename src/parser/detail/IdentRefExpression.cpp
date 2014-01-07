#include <parser/detail/IdentRefExpression.hpp>
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
IdentRefExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_ident = toker->word();
	return true;
}//parse(os, toker)

void
IdentRefExpression::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "IdentRefExpression '" << m_ident << "'" << std::endl;
}//pretty_print(os, ident)

}//namespace PL0

