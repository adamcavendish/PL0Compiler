#include <parser/detail/VarDeclStmt.hpp>
// STL
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
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/VarDecl.hpp>

namespace PL0
{

bool
VarDeclStmt::parse(std::ostream & os, std::shared_ptr<Context> context) {
	auto toker = context->getTokenizer();
	m_position = toker->position();
	bool flag = true;

	toker->next(); // eat 'var' token

	while(true) {
		auto var = auc::make_unique<VarDecl>();
		if(toker->token() == Token::tk_identifier) {
			if(var->parse(os, context)) {
				m_node_vec.push_back(std::move(var));
			} else {
				m_node_vec.push_back(std::move(var));
				flag = false;
				break;
			}//if-else

			if(toker->token() == Token::tk_comma) {
				toker->next(); // eat ',' token
			} else {
				break;
			}//if-else
		} else {
			parse_error(os, context, "A identifier token expected.");
			flag = false;
			break;
		}//if-else
	}//while

	if(flag == true) {
		if(toker->token() == Token::tk_semicolon) {
			toker->next(); // eat ';' token
		} else {
			parse_error(os, context, "A variable declaration statement must end with a ';'");
			flag = false;
		}//if-else
	}//if

	return flag;
}//parse(os, context)

void
VarDeclStmt::pretty_print(std::ostream & os, std::size_t indent) const {
	os << std::string(indent, '\t') << "VarDeclStmt " << this->position_str() << std::endl;
	for(const auto & i : m_node_vec)
		i->pretty_print(os, indent + 1);
}//pretty_print(os, indent)

llvm::Value *
VarDeclStmt::llvm_generate(std::shared_ptr<Context> context) const {
	llvm::Value * vardecl_gen = nullptr;
	for(auto & i : m_node_vec) {
		vardecl_gen = i->llvm_generate(context);
		if(vardecl_gen == nullptr) {
			generate_error(std::cerr, context, "VarDeclStmt::VarDecl llvm_generate error");
		}//if
	}//for
	return vardecl_gen;
}//llvm_generate(context)

}//namespace PL0

