#include <tokenizer/Tokenizer.hpp>

#include <iostream>

namespace PL0 {

bool Tokenizer::next() {
	using namespace std;

	// eat spaces
	m_pfb->eat_space();

	char ch = m_pfb->get();
	while(ch == '\n') {
		m_pfb->bump();
		ch = m_pfb->get();
	}//while
	m_position = std::make_pair(m_pfb->line(), m_pfb->position());

	if(ch == std::char_traits<char>::eof()) {
		m_cur_tok = Token::tk_eof;
		m_cur_tokword.clear();
	} else if(isalpha(ch)) {
		this->extractTokenAlpha();
	} else if(isdigit(ch)) {
		this->extractTokenDigit();
	} else if(m_pwordmap->is_operator(ch)) {
		this->extractTokenOperator();
	} else if(m_pwordmap->is_othersym(ch)) {
		this->extractTokenOther();
	}//if-else

	if(m_cur_tok == Token::tk_eof)
		return false;

	return true;
}//next()

void Tokenizer::extractTokenAlpha() {
	using namespace std;
	m_cur_tokword.clear();

	char ch = m_pfb->get();
	while(isalnum(ch)) {
		m_pfb->bump();
		m_cur_tokword += ch;

		ch = m_pfb->get();
	}//while

	// if it's not an preserved word, it must be an identifier
	if(m_pwordmap->get_word_token(m_cur_tokword, m_cur_tok) == false)
		m_cur_tok = Token::tk_identifier;
}//extractTokenAlpha()

void Tokenizer::extractTokenDigit() {
	using namespace std;
	m_cur_tokword.clear();

	char ch = m_pfb->get();
	while(isdigit(ch)) {
		m_pfb->bump();
		m_cur_tokword += ch;

		ch = m_pfb->get();
	}//while

	// ch can be blank or \n now, or it'll be an error token
	if(!isspace(ch)) {
		m_cur_tok = Token::tk_error;

		// extract the rest part of the current token and set it to an error
		while(isalnum(ch)) {
			m_pfb->bump();
			m_cur_tokword += ch;

			ch = m_pfb->get();
		}//while
	}//if

	// come to here it'll be safely a number token
	m_cur_tok = Token::tk_number;
}//extractTokenDigit()

void Tokenizer::extractTokenOperator() {
	m_cur_tokword.clear();

	char ch = m_pfb->get();
	while(m_pwordmap->is_operator(ch)) {
		m_pfb->bump();
		m_cur_tokword += ch;

		ch = m_pfb->get();
	}//while

	// if it's not an preserved operator, it must be an error
	if(m_pwordmap->get_op_token(m_cur_tokword, m_cur_tok) == false)
		m_cur_tok = Token::tk_error;
}//extractTokenOperator()

void Tokenizer::extractTokenOther() {
	m_cur_tokword.clear();

	char ch = m_pfb->get();
	while(m_pwordmap->is_othersym(ch)) {
		m_pfb->bump();
		m_cur_tokword += ch;

		ch = m_pfb->get();
	}//while

	// if it's not an preserved othersym, it must be an error
	if(m_pwordmap->get_othersym_token(m_cur_tokword, m_cur_tok) == false)
		m_cur_tok = Token::tk_error;
}//extractTokenOther()

}//namespace PL0

