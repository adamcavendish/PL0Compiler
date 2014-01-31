#include <parser/detail/IfStmt.hpp>
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
#include <parser/detail/CondStmt.hpp>
#include <parser/detail/Statement.hpp>
// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace PL0
{

bool
IfStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat the 'if' token

	auto condstmt = auc::make_unique<CondStmt>();
	if(!condstmt->parse(os, context))
		flag = false;
	m_condition_node = std::move(condstmt);

	if(flag == true) {
		if(toker->token() != Token::tk_then) {
			flag = false;
			parse_error(os, context, "Expect `then` token after if");
		} else {
			toker->next(); // eat `then` token
		}//if-else
	}//if

	if(flag == true) {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, context))
			flag = false;
		m_iftrue_node = std::move(stmt);
	}//if

	return flag;
}//parse(os, context)

void
IfStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "IfStmt " << this->position_str() << std::endl;

	if(m_condition_node)
		m_condition_node->pretty_print(os, indent+1);

	if(m_iftrue_node)
		m_iftrue_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
IfStmt::llvm_generate(std::shared_ptr<Context> context) const {
    llvm::Value * condgen = m_condition_node->llvm_generate(context);
    if(condgen == nullptr) {
        generate_error(std::cerr, context, "IfStmt->CondStmt llvm_generate error");
        return nullptr;
    }//if
	
    llvm::Function * func = context->getIRBuilder_llvm()->GetInsertBlock()->getParent();
    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    llvm::BasicBlock * thenBB = llvm::BasicBlock::Create(
            *(context->getLLVMContext_llvm()), "iftrue", func);
    llvm::BasicBlock * elseBB = llvm::BasicBlock::Create(
            *(context->getLLVMContext_llvm()), "iffalse");
    llvm::BasicBlock * mergeBB = llvm::BasicBlock::Create(
            *(context->getLLVMContext_llvm()), "ifmerge");
    context->getIRBuilder_llvm()->CreateCondBr(condgen, thenBB, elseBB);

    // Emit then value.
    context->getIRBuilder_llvm()->SetInsertPoint(thenBB);

    llvm::Value * thengen = m_iftrue_node->llvm_generate(context);
    if(thengen == nullptr) {
        generate_error(std::cerr, context, "IfStmt->Statement llvm_generate error");
        return nullptr;
    }//if

    context->getIRBuilder_llvm()->CreateBr(mergeBB);
    // Code generation of 'then' can change the current block, update thenBB for the PHI.
    thenBB = context->getIRBuilder_llvm()->GetInsertBlock();

#if 0
    /*
     * since we do not have a else block in PL0
     */
    // Emit else block.
    
    // push_back because `elseBB` was not added to the func when created back to `CreateCondBr` place
    func->getBasicBlockList().push_back(elseBB);
    context->getIRBuilder_llvm()->SetInsertPoint(elseBB);

    llvm::Value * elsegen = iffalse_node->llvm_generate(context);
    if (elsegen == nullptr) {
        generate_error(std::cerr, context, "IfStmt->Statement llvm_generate error");
        return nullptr;
    }//if

    context->getIRBuilder_llvm()->CreateBr(mergeBB);
    // Code generation of 'else' can change the current block, update elseBB for the PHI.
    elseBB = context->getIRBuilder_llvm()->GetInsertBlock();
#endif

    // Emit merge block.
    
    // push_back because `mergeBB` was not added to the func when created back
    // to `CreateCondBr` place
    func->getBasicBlockList().push_back(mergeBB);
    context->getIRBuilder_llvm()->SetInsertPoint(mergeBB);
    llvm::PHINode * phinode = context->getIRBuilder_llvm()->CreatePHI(
            llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())), 1, "ifphi");
    phinode->addIncoming(thengen, thenBB);

    return phinode;
}//llvm_generate(context)

}//namespace PL0

