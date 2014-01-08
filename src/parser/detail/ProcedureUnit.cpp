#include <parser/detail/ProcedureUnit.hpp>
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
#include <parser/detail/ProcedureDecl.hpp>
#include <parser/detail/BlockUnit.hpp>

namespace PL0
{

bool
ProcedureUnit::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	auto proc_decl = auc::make_unique<ProcedureDecl>();
	if(!proc_decl->parse(os, toker))
		flag = false;
	m_proc_node = std::move(proc_decl);

	auto block = auc::make_unique<BlockUnit>();
	if(!block->parse(os, toker))
		flag = false;
	m_block = std::move(block);

	if(flag == true) {
		if(toker->token() != Token::tk_semicolon) {
			flag = false;
			parse_error(os, toker, "A ';' expected after a whole procedure definition.");
		} else {
			toker->next(); // eat the current ';' token
		}//if-else
	}//if

	return flag;
}//parse(os, toker)

void
ProcedureUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "ProcedureUnit " << this->position_str() << std::endl;

	if(m_proc_node)
		m_proc_node->pretty_print(os, indent+1);
	if(m_block)
		m_block->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

