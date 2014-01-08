#pragma once

// STL
#include <iostream>
#include <memory>
#include <string>

namespace PL0 {

class Tokenizer;

void
parse_error(std::ostream & os, std::shared_ptr<Tokenizer> toker, const std::string & err_msg);

}//namespace PL0

