#include <parser/detail/Expression.hpp>
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
#include <parser/detail/ParserBase.hpp>
#include <parser/detail/MultiplicativeExpression.hpp>

namespace PL0
{

bool
Expression::parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) {
	m_position = toker->position();
	bool flag = true;

	if(flag == true) {
		auto multi = auc::make_unique<MultiplicativeExpression>();
		if(!multi->parse(os, toker))
			flag = false;
		m_node_first = std::move(multi);
	}//if

	while(flag == true) {
		std::pair<Operator, std::unique_ptr<ParserBase> > node;

		if(toker->token() == Token::tk_plus) {
			node.first.m_op = '+';
			node.first.m_position = toker->position();
		} else if(toker->token() == Token::tk_minus) {
			node.first.m_op = '-';
			node.first.m_position = toker->position();
		} else {
			break;
		}//if-else
		toker->next(); // Eat the current operator

		auto multi = auc::make_unique<MultiplicativeExpression>();
		if(!multi->parse(os, toker))
			flag = false;

		node.second = std::move(multi);
		m_nodes.push_back(std::move(node));
	}//while

	return flag;
}//parse(os, toker)

void
Expression::pretty_print(std::ostream & os, std::size_t ident) const {
#ifndef NDEBUG
	os << std::string(ident, '\t') << "Expression(debug) " << this->position_str() << std::endl;
#endif//NDEBUG

	std::function<void(int, std::size_t)> print_helper = [&](int rec, std::size_t rec_ident) {
		os << std::string(rec_ident, '\t')
			<< "Binary Operator <" << m_nodes[rec].first.m_position.first
			<< "," << m_nodes[rec].first.m_position.second
			<< "> '" << m_nodes[rec].first.m_op << "'" << std::endl;

		if(rec == 0) {
			if(m_node_first)
				m_node_first->pretty_print(os, rec_ident+1);
			if(m_nodes[0].second)
				m_nodes[0].second->pretty_print(os, rec_ident+1);
			return;
		}//if

		print_helper(rec-1, rec_ident+1);

		if(m_nodes[rec].second)
			m_nodes[rec].second->pretty_print(os, rec_ident+1);
	};//lambda print_helper(rec)

	auto sz = m_nodes.size();
	if(sz > 0) {
		print_helper(sz-1, ident);
	} else {
		if(m_node_first)
			m_node_first->pretty_print(os, ident);
	}//if-else
}//pretty_print(os, ident)

}//namespace PL0

