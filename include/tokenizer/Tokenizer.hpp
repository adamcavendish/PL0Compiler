#pragma once

// STL
#include <string>
#include <memory>
#include <utility>
// PL0Compiler
#include <preprocess.hpp>
#include <filebuf/FileBuf.hpp>
#include <token.hpp>
#include <lexer/WordMap.hpp>

namespace PL0 {

class Tokenizer {
PL0_PUBLIC: //functions
	Tokenizer(const std::shared_ptr<FileBuf> fb, const std::shared_ptr<WordMap> wordmap) :
		m_pfb(fb),
		m_cur_tok(Token::tk_eof),
		m_cur_tokword(),
		m_position(),
		m_pwordmap(wordmap)
	{}

	~Tokenizer() {}

	Tokenizer(const Tokenizer & rhs) = delete;
	Tokenizer(Tokenizer && rhs) = delete;
	Tokenizer & operator=(const Tokenizer & rhs) = delete;
	Tokenizer & operator=(Tokenizer && rhs) = delete;

	/**
	 * @brief ask Tokenizer get next token and word
	 */
	bool
	next();

	/**
	 * @brief return the current token
	 */
	inline Token 
	token() const
	{ return m_cur_tok; }
	
	/**
	 * @brief return the current word
	 */
	inline std::string
	word() const
	{ return m_cur_tokword; }

	/**
	 * @brief return the position of the current token
	 */
	inline std::pair<std::size_t, std::size_t>
	position() const
	{ return m_position; }
PL0_PRIVATE: // functions
	/**
	 * @brief helper function to extract tokens that starts with an alphabetic character
	 */
	void extractTokenAlpha();

	/**
	 * @brief helper function to extract tokens that starts with a digit
	 */
	void extractTokenDigit();

	/**
	 * @brief helper function to extract tokens of an operator
	 */
	void extractTokenOperator();

PL0_PRIVATE: // members
	/// @brief the file buffer that handles the source code file
	std::shared_ptr<FileBuf> m_pfb;
	/// @brief the current token
	Token m_cur_tok;
	/// @brief the current word corresponding to the token
	std::string m_cur_tokword;
	/// @brief the position of current token, <line, position>
	std::pair<std::size_t, std::size_t> m_position;
	/// @brief the WordMap to get token mapped from string
	std::shared_ptr<WordMap> m_pwordmap;
};//class Tokenizer

}//namespace PL0

