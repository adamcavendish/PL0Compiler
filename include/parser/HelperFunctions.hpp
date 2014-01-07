#pragma once

// STL
#include <memory>
#include <string>

namespace PL0 {

class Tokenizer;

void
parse_error(std::shared_ptr<Tokenizer> toker, const std::string & err_msg);

}//namespace PL0

