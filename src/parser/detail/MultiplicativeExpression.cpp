#include <parser/detail/MultiplicativeExpression.hpp>
// STL
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <functional>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <token.hpp>
#include <preprocess.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <parser/HelperFunctions.hpp>

namespace PL0
{

bool
MultiplicativeExpression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	bool flag = true;

	if(flag == true) {
		auto unary = auc::make_unique<UnaryExpression>();
		if(unary->parse(os, toker)) {
			m_node_first = std::move(unary);
		} else {
			flag = false;
		}//if-else
	}//if

	while(flag == true) {
		std::pair<Operator, std::unique_ptr<ParserBase>> node;
		if(toker->token() == Token::tk_multiply) {
			node.first = '*';
		} else if(toker->token() == Token::tk_divide) {
			node.first = '/';
		} else {
			break;
		}//if-else

		toker->next(); // Eat the current operator
		auto unary = auc::make_unique<UnaryExpression>();
		if(unary->parse(os, toker)) {
			node.second = std::move(unary);
			m_nodes.push_back(std::move(node));
		} else {
			flag = false;
		}//if-else
	}//while

	return flag;
}//parse(os, toker)

void
MultiplicativeExpression::pretty_print(std::ostream & os, std::size_t ident) const {
	std::function<void(int, std::size_t)> print_helper = [&](int rec, std::size_t rec_ident) {
		os << std::string(rec_ident, '\t')
			<< "Binary Operator '" << m_nodes[rec].first << "'" << std::endl;

		if(rec == 0) {
			m_node_first->pretty_print(os, rec_ident);
			m_nodes[0].second->pretty_print(os, rec_ident);
			return;
		}//if

		print_helper(rec-1, rec_ident+1);
		m_nodes[rec].second->pretty_print(os, rec_ident);
	};//lambda print_helper(rec)

	auto sz = m_nodes.size();
	if(sz > 0) {
		print_helper(sz - 1, ident);
	} else {
		m_node_first->pretty_print(os, ident);
	}//if-else
}//pretty_print(os, ident)

}//namespace PL0

