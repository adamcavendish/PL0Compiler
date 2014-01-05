// STL
#include <iostream>
#include <string>
#include <map>
#include <memory>
// C-STL
#include <cctype>
// PL0Compiler
#include <tokenizer/all.hpp>

using namespace PL0;

int
to_int(const std::string & str)
{
	int ret = 0;

	for(auto i : str) {
		ret += (i - '0');
		ret *= 10;
	}//for
	ret /= 10;

	return ret;
}//to_int()

int main()
{
	std::map<Token, std::string> mmap = {
		{ Token::tk_const, "constsym" },
		{ Token::tk_identifier, "ident" },
		{ Token::tk_equal, "eql" },
		{ Token::tk_number, "number" },
		{ Token::tk_semicolon, "semicolon" },
		{ Token::tk_begin, "beginsym" },
		{ Token::tk_read, "readsym" },
		{ Token::tk_lparenthesis, "lparen" },
		{ Token::tk_rparenthesis, "rparen" },
		{ Token::tk_assign, "becomes" },
		{ Token::tk_plus, "plus" },
		{ Token::tk_write, "writesym" },
		{ Token::tk_end, "endsym" },
		{ Token::tk_period, "period" },
		{ Token::tk_comma, "comma" },
		{ Token::tk_var, "varsym" },
	};

	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("win.pl0");

	Tokenizer toker(pfb, pwm);
	while(toker.next()) {
		if(toker.token() == Token::tk_number) {
			std::cout << "(" << mmap[toker.token()] << ", " << to_int(toker.word()) << ")" << std::endl;
		} else {
			std::cout << "(" << mmap[toker.token()] << ", " << toker.word() << ")" << std::endl;
		}//if-else
	}//while

	return 0;
}//main

