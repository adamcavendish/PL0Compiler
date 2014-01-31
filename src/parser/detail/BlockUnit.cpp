#include <parser/detail/BlockUnit.hpp>
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
#include <symtable/SymTable.hpp>
#include <symtable/SymTable_llvm.hpp>
#include <parser/HelperFunctions.hpp>
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/ConstDeclStmt.hpp>
#include <parser/detail/VarDeclStmt.hpp>
#include <parser/detail/Expression.hpp>
#include <parser/detail/ProcedureUnit.hpp>
#include <parser/detail/Statement.hpp>

namespace PL0 {

bool
BlockUnit::parse(std::ostream & os, std::shared_ptr<Context> context) {
	m_position = context->getTokenizer()->position();
	bool flag = true;

	if(context->getTokenizer()->token() == Token::tk_const) {
		auto cdecl = auc::make_unique<ConstDeclStmt>();
		if(!cdecl->parse(os, context))
			flag = false;
		m_const_decl_stmt = std::move(cdecl);
	}//if
	
	if(context->getTokenizer()->token() == Token::tk_var) {
		auto vdecl = auc::make_unique<VarDeclStmt>();
		if(!vdecl->parse(os, context))
			flag = false;
		m_var_decl_stmt = std::move(vdecl);
	}//if-else

	while(flag == true && context->getTokenizer()->token() == Token::tk_procedure) {
		auto proc_unit = auc::make_unique<ProcedureUnit>();
		if(!proc_unit->parse(os, context))
			flag = false;
		m_procedures.push_back(std::move(proc_unit));
	}//while

	if(flag == true) {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, context))
			flag = false;
		m_statement = std::move(stmt);
	}//if
	
	return flag;
}//parse(os, context)

void
BlockUnit::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "BlockUnit " << this->position_str() << std::endl;
	
	if(m_const_decl_stmt)
		m_const_decl_stmt->pretty_print(os, indent+1);
	if(m_var_decl_stmt)
		m_var_decl_stmt->pretty_print(os, indent+1);
	for(const auto & i : m_procedures)
		i->pretty_print(os, indent+1);
	if(m_statement)
		m_statement->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
BlockUnit::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;
    // reserve current InsertBlock, so that after `procedures`.
    llvm::BasicBlock * bb = context->getIRBuilder_llvm()->GetInsertBlock();
	context->getSymTable_llvm()->createLocalSymTable();

    if(m_const_decl_stmt != nullptr) {
        llvm::Value * const_decl_stmt_gen = m_const_decl_stmt->llvm_generate(context);
        if(const_decl_stmt_gen == nullptr) {
            generate_error(std::cerr, context, "BlockUnit->ConstDeclStmt llvm_generate error");
            flag = false;
        }//if
    }//if

    if(m_var_decl_stmt != nullptr) {
        llvm::Value * var_decl_stmt_gen = m_var_decl_stmt->llvm_generate(context);
        if(var_decl_stmt_gen == nullptr) {
            generate_error(std::cerr, context, "BlockUnit->VarDeclStmt llvm_generate error");
            flag = false;
        }//if
    }//if

	for(auto & i : m_procedures) {
		llvm::Value * procedure_gen = i->llvm_generate(context);
		if(procedure_gen == nullptr) {
			generate_error(std::cerr, context, "BlockUnit->ProcedureUnit llvm_generate error");
			flag = false;
		}//if
	}//for

    context->getIRBuilder_llvm()->SetInsertPoint(bb);
    if(m_statement != nullptr) {
        llvm::Value * statement_gen = m_statement->llvm_generate(context);
        if(statement_gen == nullptr) {
            generate_error(std::cerr, context, "BlockUnit->Statement llvm_generate error");
            flag = false;
        }//if
    }//if

	context->getSymTable_llvm()->dropLocalSymTable();

	if(flag == true) {
		return llvm::Constant::getNullValue(
                llvm::Type::getInt32Ty(*(context->getLLVMContext_llvm())));
    }//if
    return nullptr;
}//llvm_generate(context)

}//namespace PL0

