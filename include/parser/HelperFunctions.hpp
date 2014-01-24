#pragma once

// STL
#include <iostream>
#include <memory>
#include <string>

namespace PL0 {

class Context;

void
parse_error(std::ostream & os, std::shared_ptr<Context> context, const std::string & err_msg);

}//namespace PL0

