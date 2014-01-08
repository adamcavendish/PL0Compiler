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
	m_position = toker->position();
	bool flag = true;

	if(flag == true) {
		auto unary = auc::make_unique<UnaryExpression>();
		if(!unary->parse(os, toker))
			flag = false;
		m_node_first = std::move(unary);
	}//if

	while(flag == true) {
		std::pair<Operator, std::unique_ptr<ParserBase>> node;

		if(toker->token() == Token::tk_multiply) {
			node.first.m_op = '*';
			node.first.m_position = toker->position();
		} else if(toker->token() == Token::tk_divide) {
			node.first.m_op = '/';
			node.first.m_position = toker->position();
		} else {
			break;
		}//if-else
		toker->next(); // Eat the current operator

		auto unary = auc::make_unique<UnaryExpression>();
		if(!unary->parse(os, toker))
			flag = false;

			node.second = std::move(unary);
			m_nodes.push_back(std::move(node));
	}//while

	return flag;
}//parse(os, toker)

void
MultiplicativeExpression::pretty_print(std::ostream & os, std::size_t indent) const {
#ifndef NDEBUG
	os << std::string(indent, '\t') << "MultiplicativeExpression(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	std::function<void(int, std::size_t)> print_helper = [&](int rec, std::size_t rec_indent) {
		os << std::string(rec_indent, '\t')
			<< "BinaryOperator <" << m_nodes[rec].first.m_position.first << ","
			<< m_nodes[rec].first.m_position.second << ">"
			<< " '" << m_nodes[rec].first.m_op << "'" << std::endl;

		if(rec == 0) {
			if(m_node_first)
				m_node_first->pretty_print(os, rec_indent+1);
			if(m_nodes[0].second)
				m_nodes[0].second->pretty_print(os, rec_indent+1);
			return;
		}//if

		print_helper(rec-1, rec_indent+1);

		if(m_nodes[rec].second)
			m_nodes[rec].second->pretty_print(os, rec_indent+1);
	};//lambda print_helper(rec)

	auto sz = m_nodes.size();
	if(sz > 0) {
		print_helper(sz-1, indent);
	} else {
		if(m_node_first)
			m_node_first->pretty_print(os, indent);
	}//if-else
}//pretty_print(os, indent)

}//namespace PL0

