#include <parser/detail/CallStmt.hpp>
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
#include <parser/detail/FunctionRefExpression.hpp>

namespace PL0
{

bool
CallStmt::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat the 'call' token

	auto func_ref = auc::make_unique<FunctionRefExpression>();
	if(!func_ref->parse(os, toker))
		flag = false;
	m_node = std::move(func_ref);

	return flag;
}//parse(os, toker)

void
CallStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "CallStmt " << this->position_str() << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

}//namespace PL0

