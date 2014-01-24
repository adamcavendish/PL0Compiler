#include <parser/HelperFunctions.hpp>
// STL
#include <iostream>
#include <string>
// PL0Compiler
#include <context/Context.hpp>
#include <tokenizer/Tokenizer.hpp>

namespace PL0 {

void
parse_error(std::ostream & os, std::shared_ptr<Context> context, const std::string & err_msg) {
	os << "Error at " << context->getTokenizer()->position().first << ":" << context->getTokenizer()->position().second <<
		" " << err_msg << std::endl;
	os << "Current token: <" << context->getTokenizer()->token()
		<< ":'" << context->getTokenizer()->word() << "'>" << std::endl;
}//parse_error(context, err_msg)

}//namespace PL0

