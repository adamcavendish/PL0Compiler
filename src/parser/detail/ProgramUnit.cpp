#include <parser/detail/ProgramUnit.hpp>
// STL
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
#include <parser/detail/BlockUnit.hpp>

namespace PL0
{

bool
ProgramUnit::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	bool flag = true;

	auto block = auc::make_unique<BlockUnit>();

	if(block->parse(os, toker)) {
		m_node = std::move(block);
	} else {
		flag = false;
	}//if-else

	if(flag == true && toker->token() == Token::tk_period) {
		toker->next(); // eat '.' token
	} else {
		parse_error(toker, "A program needs to be ended with a '.'");
		flag = false;
	}//if-else

	return flag;
}//parse(os, toker)

void
ProgramUnit::pretty_print(std::ostream & os, std::size_t ident) const {
	os << std::string(ident, '\t') << "ProgramUnit" << std::endl;
	m_node->pretty_print(os, ident + 1);
}//pretty_print(os, ident)

}//namespace PL0

