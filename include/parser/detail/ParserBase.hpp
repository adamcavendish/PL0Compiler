#pragma once

// STL
#include <memory>
// PL0Compiler
#include <preprocess.hpp>

namespace PL0
{

class Tokenizer;

/**
 * @brief the base object of all parsers
 */
class ParserBase
{
PL0_PUBLIC:
	/**
	 * @brief All parsers should be moveable but non-copyable
	 */
	virtual
	ParserBase(ParserBase && rhs) = 0;

	/**
	 * @brief All parsers should be move-assignable but non-copy-assignable
	 */
	virtual ParserBase &
	operator=(ParserBase && rhs) = 0;

	/**
	 * @brief parse function should do the corresponding parsing work
	 */
	virtual bool
	parse(std::shared_ptr<Tokenizer> toker) = 0;

	/**
	 * @brief pretty_print function will print the abstruct-syntax-tree in a human-readable way.
	 */
	/*
	virtual void
	pretty_print() = 0;
	 */

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
	~ParserBase() = 0;

PL0_PRIVATE:
	/**
	 * @brief Making the derived class non-copyable.
	 *		This will cause a link-time error if it actually defined and
	 *		used the copy construction.
	 *		However it is always a good habit to define the copy constructor
	 *		of the derived Parsers `deleted`. @see ConstVarDecl.hpp for example.
	 */
	ParserBase(const ParserBase & rhs) final;

	/**
	 * @brief Making the derived class non-copy-assignable.
	 *		This will cause a link-time error if it actually defined and
	 *		used the copy assignment.
	 *		However it is always a good habit to define the copy assign operation
	 *		of the derived Parsers `deleted`. @see ConstVarDecl.hpp for example.
	 */
	ParserBase &
	operator=(const ParserBase & rhs) final;
}//ParserBase


}//namespace PL0
