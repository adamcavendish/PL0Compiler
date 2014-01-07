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
	m_ident = toker->word();
	toker->next(); // eat the current identifier
	return true;
}//parse(os, toker)

void
VarDecl::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "VarDecl '" << m_ident << "'" << std::endl;
}//pretty_print(os, ident)

}//namespace PL0

