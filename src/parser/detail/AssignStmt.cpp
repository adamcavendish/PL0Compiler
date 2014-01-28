#include <parser/detail/AssignStmt.hpp>
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
#include <context/Context.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/IdentRefExpression.hpp>
#include <parser/detail/Expression.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace PL0
{

bool
AssignStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	m_position = context->getTokenizer()->position();
	bool flag = true;

	auto identref = auc::make_unique<IdentRefExpression>();
	if(!identref->parse(os, context))
		flag = false;
	m_assign_left = std::move(identref);

	if(flag == true) {
		if(context->getTokenizer()->token() != Token::tk_assign) {
			flag = false;
			parse_error(os, context, "Expect an assignment operator Here!");
		} else {
			context->getTokenizer()->next(); // eat the current ':=' operator
		}//if-else
	}//if
	
	if(flag == true) {
		auto expr = auc::make_unique<Expression>();
		if(!expr->parse(os, context))
			flag = false;
		m_assign_right = std::move(expr);
	}//if

	return flag;
}//parse(os, context)

void
AssignStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "AssignStmt " << this->position_str() << std::endl;

	if(m_assign_left)
		m_assign_left->pretty_print(os, indent+1);
	if(m_assign_right)
		m_assign_right->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
AssignStmt::llvm_generate(std::shared_ptr<Context> context) const {
	llvm::Value * L = m_assign_left->llvm_generate(context);
	llvm::Value * R = m_assign_right->llvm_generate(context);

	context->getIRBuilder_llvm()->CreateStore(L, R);
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

