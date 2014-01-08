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
	m_position = toker->position();
	bool flag = true;

	auto block = auc::make_unique<BlockUnit>();

	if(!block->parse(os, toker))
		flag = false;
	m_node = std::move(block);

	if(flag == true) {
		if(toker->token() == Token::tk_period) {
			toker->next(); // eat '.' token
		} else {
			parse_error(os, toker, "A program needs to be ended with a '.'");
			flag = false;
		}//if-else
	}//if

	return flag;
}//parse(os, toker)

void
ProgramUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProgramUnit " << this->position_str() << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

