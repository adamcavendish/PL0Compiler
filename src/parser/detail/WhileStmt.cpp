#include <parser/detail/WhileStmt.hpp>
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

namespace PL0
{

bool
WhileStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat the 'while' token

	auto condstmt = auc::make_unique<CondStmt>();
	if(!condstmt->parse(os, context))
		flag = false;
	m_condition_node = std::move(condstmt);

	if(flag == true) {
		if(toker->token() != Token::tk_do) {
			flag = false;
			parse_error(os, context, "Expect `do` token after while");
		} else {
			 toker->next(); // eat `do` token
		}//if-else
	}//if

	if(flag == true) {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, context))
			flag = false;
		m_stmt_node = std::move(stmt);
	}//if

	return flag;
}//parse(os, context)

void
WhileStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "WhileStmt " << this->position_str() << std::endl;

	if(m_condition_node)
		m_condition_node->pretty_print(os, indent+1);

	if(m_stmt_node)
		m_stmt_node->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
WhileStmt::llvm_generate(std::shared_ptr<Context> context) const {
	llvm::Value * cond_gen = m_condition_node->llvm_generate(context);
	if(cond_gen == nullptr) {
		generate_error(std::cerr, context, "WhileStmt::CondStmt llvm_generate error");
		return nullptr;
	}//if

	llvm::Value * stmt_gen = m_stmt_node->llvm_generate(context);
	if(stmt_gen == nullptr) {
		generate_error(std::cerr, context, "WhileStmt::Statement llvm_generate error");
		return nullptr;
	}

	return cond_gen;
}//llvm_generate(context)

}//namespace PL0

