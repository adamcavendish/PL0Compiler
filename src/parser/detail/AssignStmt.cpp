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
    auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

    if(toker->token() != Token::tk_identifier) {
        flag = false;
        parse_error(os, context, "Expect an identifier here!");
    } else {
	    m_assign_left = toker->word();
        toker->next(); // eat current identifier
    }//if-else

	if(flag == true) {
		if(toker->token() != Token::tk_assign) {
			flag = false;
			parse_error(os, context, "Expect an assignment operator here!");
		} else {
			toker->next(); // eat the current ':=' operator
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
	os << std::string(indent, '\t') << "AssignStmt " << this->position_str()
        << " '" << m_assign_left << "'" << std::endl;

	if(m_assign_right)
		m_assign_right->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
AssignStmt::llvm_generate(std::shared_ptr<Context> context) const {
    // Emit the initializer before adding the variable to scope, this prevents
    // the initializer from referencing the variable itself,
    
	llvm::Value * R = m_assign_right->llvm_generate(context);
    if(R == nullptr) {
        generate_error(std::cerr, context, "AssignStmt->Expression llvm_generate error");
        return nullptr;
    }//if

	llvm::Value * ident = context->lookupVariable_llvm(m_assign_left);
    if(ident == nullptr) {
        generate_error(std::cerr, context,
                "undefined assignment of variable: " + m_assign_left);
        return nullptr;
    }//if

	auto store = context->getIRBuilder_llvm()->CreateStore(R, ident);
    if(store == nullptr) {
        generate_error(std::cerr, context, "AssignStmt::llvm_generate CreateStore error");
        std::abort();
    }//if

    return llvm::Constant::getNullValue(
            llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())));
}//llvm_generate(context)

}//namespace PL0

