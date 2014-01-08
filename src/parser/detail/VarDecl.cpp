#include <parser/detail/VarDecl.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/IntegerLiteral.hpp>

namespace PL0
{

bool
VarDecl::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();

	m_ident = toker->word();
	toker->next(); // eat the current identifier

	return true;
}//parse(os, toker)

void
VarDecl::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "VarDecl "
		<< this->position_str() << " '" << m_ident << "'" << std::endl;
}//pretty_print(os, indent)

}//namespace PL0

