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
#include <context/Context.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ProcedureRefExpression.hpp>

namespace PL0
{

bool
CallStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	m_position = context->getTokenizer()->position();
	bool flag = true;

	context->getTokenizer()->next(); // eat the 'call' token

	auto func_ref = auc::make_unique<ProcedureRefExpression>();
	if(!func_ref->parse(os, context))
		flag = false;
	m_node = std::move(func_ref);

	return flag;
}//parse(os, context)

void
CallStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "CallStmt " << this->position_str() << std::endl;

	if(m_node)
		m_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
CallStmt::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::Value * func = m_node->llvm_generate(context);
	if(func == nullptr) {
		generate_error(std::cerr, context, "CallStmt->ProcedureRefExpression llvm_generate error");
		flag = false;
	}//if

	llvm::CallInst * ret = context->getIRBuilder_llvm()->CreateCall(func, "callstmt");
	if(ret == nullptr) {
		generate_error(std::cerr, context, "CallStmt::llvm_generate Call Instruction Create error");
		std::abort();
	}//if

	if(flag == true)
		return ret;
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

