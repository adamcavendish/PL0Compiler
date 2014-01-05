#include <parser/detail/ConstVarDecl.hpp>
// STL
#include <iostream>
#include <memory>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/IntegerLiteral.hpp>

namespace PL0
{

bool
ConstVarDecl::parse(std::shared_ptr<Tokenizer> toker) {
	m_ident = toker->word();

	toker->next(); // eat the current identifier

	if(toker->token() != Token::tk_equal) {
		parse_error(toker, "expect an '=' here for const identifier initialization");
		return false;
	} else {
		toker->next();
	}//if-else

	if(toker->token() == Token::tk_number) {
		// make_unique was overlooked by c++11, a simple implementation
		auto int_num = auc::make_unique<IntegerLiteral>();
		if(int_num->parse(toker)) {
			m_node = std::move(int_num);
		} else {
			return false;
		}//if-else
	} else {
		parse_error(toker, "A const declearation must be initialized with a integer number.");
		return false;
	}//if-else

	return true;
}//parser(toker)

}//namespace PL0

