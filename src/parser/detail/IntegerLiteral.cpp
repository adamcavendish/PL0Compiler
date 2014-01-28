#include <parser/detail/IntegerLiteral.hpp>
// STL
#include <iostream>
#include <stdexcept>
#include <memory>
#include <utility>
#include <vector>
#include <limits>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <context/Context.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/HelperFunctions.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace PL0
{

bool
IntegerLiteral::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	try {
		m_value = std::stoi(toker->word());
	} catch(std::invalid_argument & e) {
		parse_error(os, context, "Invalid Number format");
		flag = false;
	} catch(std::out_of_range & e) {
		parse_error(os, context, "Number out of range. limit: ["
				+ std::to_string(std::numeric_limits<int>::min())
				+ ", "
				+ std::to_string(std::numeric_limits<int>::max())
				+ "]");
		flag = false;
	}//try-catch

	toker->next(); // eat the current number

	return flag;
}//parse(os, context)

void
IntegerLiteral::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "IntegerLiteral "
		<< this->position_str() << " '" << m_value << "'" << std::endl;
}//pretty_print(os, indent)

llvm::Value *
IntegerLiteral::llvm_generate(std::shared_ptr<Context> context) const {
	return llvm::ConstantInt::get(*(context->getLLVMContext_llvm()), llvm::APInt(32, m_value));
}//llvm_generate(context)

}//namespace PL0

