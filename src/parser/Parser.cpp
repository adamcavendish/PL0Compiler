#include <parser/Parser.hpp>
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
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/ProgramUnit.hpp>

namespace PL0
{

bool
Parser::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	auto prog = auc::make_unique<ProgramUnit>();
	toker->next(); // start tokenizing

	if(prog->parse(os, toker)) {
		m_genesis = std::move(prog);
	} else {
		return false;
	}//if-else
	return true;
}//parse(os, toker)

void
Parser::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "Translation Unit" << std::endl;
	m_genesis->pretty_print(os, ident + 1);
}//pretty_print(os, ident)

}//namespace PL0

