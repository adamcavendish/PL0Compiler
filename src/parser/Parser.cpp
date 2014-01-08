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
	bool flag = true;

	toker->next(); // start tokenizing

	auto prog = auc::make_unique<ProgramUnit>();
	if(!prog->parse(os, toker))
		flag = false;

	m_genesis = std::move(prog);

	return flag;
}//parse(os, toker)

void
Parser::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "Translation Unit" << std::endl;

	if(m_genesis)
		m_genesis->pretty_print(os, indent + 1);
}//pretty_print(os, indent)

}//namespace PL0

