#pragma once

// STL
#include <iostream>
#include <string>

namespace PL0 {

class Tokenizer;

void
parse_error(std::shared_ptr<Tokenizer> toker, const std::string & err_msg) {
	std::cerr << toker.position().first << ":" << toker.position().second <<
		" " << err_msg << std::endl;
}//parse_error(toker, err_msg)

}//namespace PL0

