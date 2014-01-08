#pragma once

// STL
#include <iostream>
#include <memory>
// PL0Compiler
#include <preprocess.hpp>

namespace PL0
{

class Tokenizer;

/**
 * @brief the base object of all parsers
 *
 * All parsers should be default constructable, moveable but non-copyable,
 * move-assignable but non-copy-assignable.
 */
class ParserBase
{
PL0_PUBLIC:
	/**
	 * @brief All parsers should be default constructable
	 */
	ParserBase() {}

	/**
	 * @brief All parsers should be moveable but non-copyable
	 */
	ParserBase(ParserBase && rhs) {}

	/**
	 * @brief parse function should do the corresponding parsing work
	 */
	virtual bool
	parse(std::ostream & os, std::shared_ptr<Tokenizer> toker) = 0;

	/**
	 * @brief pretty_print function will print the abstruct-syntax-tree in a human-readable way.
	 */
	virtual void
	pretty_print(std::ostream & os, std::size_t indent) const = 0;

	/**
	 * @brief generate function will generate the intermediate code representation
	 */
	/*
	virtual void
	generate(ostream & os) = 0;
	*/

	/**
	 * @brief virtual destructor of Base Parser
	 */
	virtual
	~ParserBase() {}

	inline std::string
	position_str() const
	{ return ("<" + std::to_string(m_position.first) + "," + std::to_string(m_position.second) + ">"); }
PL0_PROTECTED:
	/**
	 * @brief m_position indicates the column and the position of the current Token
	 */
	std::pair<std::size_t, std::size_t> m_position;
};//class ParserBase

}//namespace PL0

