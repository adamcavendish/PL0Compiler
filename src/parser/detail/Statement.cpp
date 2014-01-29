#include <parser/detail/Statement.hpp>
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
#include <parser/detail/CallStmt.hpp>
#include <parser/detail/CompoundStmt.hpp>
#include <parser/detail/IfStmt.hpp>
#include <parser/detail/WhileStmt.hpp>
#include <parser/detail/CondStmt.hpp>
#include <parser/detail/AssignStmt.hpp>

namespace PL0
{

bool
Statement::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	if(toker->token() == Token::tk_call) {
		auto callstmt = auc::make_unique<CallStmt>();
		if(!callstmt->parse(os, context))
			flag = false;
		m_node = std::move(callstmt);
	} else if(toker->token() == Token::tk_begin) {
		auto compoundstmt = auc::make_unique<CompoundStmt>();
		if(!compoundstmt->parse(os, context))
			flag = false;
		m_node = std::move(compoundstmt);
	} else if(toker->token() == Token::tk_if) {
		auto ifstmt = auc::make_unique<IfStmt>();
		if(!ifstmt->parse(os, context))
			flag = false;
		m_node = std::move(ifstmt);
	} else if(toker->token() == Token::tk_while) {
		auto whilestmt = auc::make_unique<WhileStmt>();
		if(!whilestmt->parse(os, context))
			flag = false;
		m_node = std::move(whilestmt);
	} else if(toker->token() == Token::tk_identifier) {
		auto assignstmt = auc::make_unique<AssignStmt>();
		if(!assignstmt->parse(os, context))
			flag = false;
		m_node = std::move(assignstmt);
	} else {
		flag = false;
		parse_error(os, context, "A statement here should be either "
				"a `CallStmt` or `begin ... end` or `IfStmt` or `WhileStmt` or an assignment.");
	}//if-else

	return flag;
}//parse(os, context)

void
Statement::pretty_print(std::ostream & os, std::size_t indent) const {
#ifndef NDEBUG
	os << std::string(indent, '\t') << "Statement(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	if(m_node)
		m_node->pretty_print(os, indent);
}//pretty_print(os, indent)

llvm::Value *
Statement::llvm_generate(std::shared_ptr<Context> context) const {
	auto ret = m_node->llvm_generate(context);
    if(ret == nullptr) {
        generate_error(std::cerr, context, "Statement->AssignStmt llvm_generate error");
    }//if
    return ret;
}//llvm_generate(context)

}//namespace PL0

