#include <parser/detail/CompoundStmt.hpp>
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
#include <parser/detail/Statement.hpp>

namespace PL0
{

bool
CompoundStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();

	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat current token 'begin'

	do {
		auto stmt = auc::make_unique<Statement>();
		if(!stmt->parse(os, context))
			flag = false;
		m_nodes.push_back(std::move(stmt));

		if(toker->token() == Token::tk_semicolon) {
			toker->next(); // eat token ';'
		} else if(toker->token() == Token::tk_end) {
			toker->next(); // eat token 'end'
			break;
		} else {
			flag = false;
			parse_error(os, context, "Expect a ';' after every statement or an `end` to end a compound statement.");
			break;
		}//if-else
	} while(true); //do-while

	return flag;
}//parse(os, context)

void
CompoundStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "CompoundStmt " << this->position_str() << std::endl;
	for(const auto & i : m_nodes)
		i->pretty_print(os, indent+1);
}//pretty_print(os, indent)

llvm::Value *
CompoundStmt::llvm_generate(std::shared_ptr<Context> context) const {
	bool flag = true;

	llvm::Value * stmt_gen = nullptr;
	for(auto & i : m_nodes) {
		stmt_gen = i->llvm_generate(context);
		if(stmt_gen == nullptr) {
			generate_error(std::cerr, context, "CompoundStmt->Statement llvm_generate errror");
			flag = false;
		}//if
	}//for

	if(flag == true)
		return stmt_gen;
	return nullptr;
}//llvm_generate(context)

}//namespace PL0

