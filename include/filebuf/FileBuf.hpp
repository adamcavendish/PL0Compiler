#pragma once

// STL
#include <streambuf>
#include <fstream>
#include <string>
// C-STL
#include <cctype>
// PL0Compiler
#include <preprocess.hpp>

namespace PL0 {

class FileBuf {
PL0_PUBLIC: //functions
	FileBuf(const std::string & filepath) :
		m_last_char(),
		m_file(filepath),
		m_pbuf(m_file.rdbuf()),
		m_line_num(1),
		m_pos_num(0)
	{}

	~FileBuf() {}

	FileBuf(const FileBuf & rhs) = delete;
	FileBuf(FileBuf && rhs) = delete;
	FileBuf & operator=(const FileBuf & rhs) = delete;
	FileBuf & operator=(FileBuf && rhs) = delete;

	/**
	 * @brief returns the character at the current position
	 */
	char
	get();

	/**
	 * @brief returns the character at the current position and advances the current position to the next
	 */
	char
	bump();

	/**
	 * @brief advances the current position to the next and return this next character.
	 */
	char
	next();

	/**
	 * @brief decrease the current position. Only one time unget is guaranteed.
	 *
	 * @return on success, return true; on failure, return false
	 *
	 * FIXME: this function will cause error at the edge of a newline under windows and mac
	 */
	inline bool
	unget();

	/**
	 * @brief get current line number
	 */
	inline std::size_t
	line() const
	{ return m_line_num; }

	/**
	 * @brief get current position at the current line
	 */
	inline std::size_t
	position() const
	{ return m_pos_num; }

	/**
	 * @brief eat all '\t' and ' ' characters
	 *
	 * @return returns the number of characters eaten
	 *
	 * After calling `eat_space()' function, get() function will return the first character that is not blank
	 *
	 */
	inline std::size_t
	eat_space();

PL0_PRIVATE: //functions
	/**
	 * @brief check whether to eat one character to unify the format of newline
	 *
	 * @return true if need to process the next character, false if need not.
	 */
	inline bool
	check_at_newline(const char cur_char) const;

PL0_PRIVATE: //members
	char m_last_char;
	std::ifstream m_file;
	std::streambuf * m_pbuf;
	std::size_t m_line_num;
	std::size_t m_pos_num;
};//class FileBuf

std::size_t
FileBuf::eat_space() {
	using namespace std;
	std::size_t ret = 0;
	char ch = this->get();
	while(isblank(ch)) {
		this->bump();
		ch = this->get();
	}//while

	return ret;
}//eat_spaces()

bool
FileBuf::unget() {
	bool ret = m_pbuf->sungetc() != std::char_traits<char>::eof();
	if(ret)
		--m_pos_num;
	return ret;
}//unget()

bool
FileBuf::check_at_newline(const char cur_char) const {
	if(m_last_char == '\n' || m_last_char == '\r') {
		if((m_last_char == '\n' && cur_char == '\r') ||
				(m_last_char == '\r' && cur_char == '\n'))
		{
			return true;
		}//if
	}//if

	return false;
}//check_at_newline()

}//namespace PL0


