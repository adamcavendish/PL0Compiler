#include <parser/detail/ProcedureRefExpression.hpp>
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
ProcedureRefExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();

	m_ident = toker->word();
	return true;
}//parse(os, toker)

void
ProcedureRefExpression::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProcedureRefExpression "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

}//namespace PL0

