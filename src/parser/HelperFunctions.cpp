#include <parser/HelperFunctions.hpp>
// STL
#include <iostream>
#include <string>
// PL0Compiler
#include <tokenizer/Tokenizer.hpp>

namespace PL0 {

void
parse_error(std::ostream & os, std::shared_ptr<Tokenizer> toker, const std::string & err_msg) {
	os << "Error at " << toker->position().first << ":" << toker->position().second <<
		" " << err_msg << std::endl;
	os << "Current token: <" << toker->token() << ":'" << toker->word() << "'>" << std::endl;
}//parse_error(toker, err_msg)

}//namespace PL0

