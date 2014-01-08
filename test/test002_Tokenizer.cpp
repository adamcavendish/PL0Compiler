// STL
#include <iostream>
#include <memory>
#include <string>
// gtest
#include <gtest/gtest.h>
// PL0Compiler
#include <tokenizer/Tokenizer.hpp>

using namespace PL0;

TEST(TokenizerTest, chk_construction) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("win.pl0");

	Tokenizer toker(pfb, pwm);
	SUCCEED();
}

TEST(TokenizerTest, chk_next) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("win.pl0");

	std::string expected = 
		"1002: `const': <1, 1>\n"
		"2000: `a': <1, 7>\n"
		"4004: `=': <1, 8>\n"
		"3000: `10': <1, 9>\n"
		"5003: `;': <1, 11>\n"
		"1010: `var': <2, 1>\n"
		"2000: `b': <2, 5>\n"
		"5002: `,': <2, 6>\n"
		"2000: `c': <2, 7>\n"
		"5003: `;': <2, 8>\n"
		"1000: `begin': <3, 1>\n"
		"1008: `read': <4, 1>\n"
		"5000: `(': <4, 5>\n"
		"2000: `b': <4, 6>\n"
		"5001: `)': <4, 7>\n"
		"5003: `;': <4, 8>\n"
		"2000: `c': <5, 1>\n"
		"4010: `:=': <5, 2>\n"
		"2000: `a': <5, 4>\n"
		"4000: `+': <5, 5>\n"
		"2000: `b': <5, 6>\n"
		"5003: `;': <5, 7>\n"
		"1012: `write': <6, 1>\n"
		"5000: `(': <6, 6>\n"
		"2000: `c': <6, 7>\n"
		"5001: `)': <6, 8>\n"
		"5003: `;': <6, 9>\n"
		"1004: `end': <7, 1>\n"
		"5004: `.': <7, 4>\n";

	std::string comp;
	Tokenizer toker(pfb, pwm);
	while(toker.next()) {
		if(toker.token() == Token::tk_error)
			FAIL();
		comp += std::to_string(toker.token());
		comp += ": `";
		comp += toker.word();
		comp += "': <";
		comp += std::to_string(toker.position().first);
		comp += ", ";
		comp += std::to_string(toker.position().second);
		comp += ">";
		comp += "\n";
	}//while

	std::cout << expected << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << comp << std::endl;
	ASSERT_EQ(expected, comp);
}

TEST(TokenizerTest, file01) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("file01.pl0");
	
	std::string comp;
	Tokenizer toker(pfb, pwm);
	while(toker.next()) {
		if(toker.token() == Token::tk_error)
			FAIL();
		comp += std::to_string(toker.token());
		comp += ": `";
		comp += toker.word();
		comp += "': <";
		comp += std::to_string(toker.position().first);
		comp += ", ";
		comp += std::to_string(toker.position().second);
		comp += ">";
		comp += "\n";
	}//while
	
	std::cout << comp << std::endl;
	SUCCEED();
}

TEST(TokenizerTest, file02) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("file02.pl0");
	
	std::string comp;
	Tokenizer toker(pfb, pwm);
	while(toker.next()) {
		if(toker.token() == Token::tk_error)
			FAIL();
		comp += std::to_string(toker.token());
		comp += ": `";
		comp += toker.word();
		comp += "': <";
		comp += std::to_string(toker.position().first);
		comp += ", ";
		comp += std::to_string(toker.position().second);
		comp += ">";
		comp += "\n";
	}//while
	
	std::cout << comp << std::endl;
	SUCCEED();
}

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);

	std::string code;
	std::ofstream ofs;

	ofs.open("win.pl0");
	code =
		"const a=10;\r\n"
		"var b,c;\r\n"
		"begin\r\n"
		"read(b);\r\n"
		"c:=a+b;\r\n"
		"write(c);\r\n"
		"end.\r\n"
		"\r\n";
	ofs << code;
	ofs.close();

	ofs.open("mac.pl0");
	code =
		"const a=10;\r"
		"var b,c;\r"
		"begin\r"
		"read(b);\r"
		"c:=a+b;\r"
		"write(c);\r"
		"end.\r"
		"\r";
	ofs << code;
	ofs.close();

	ofs.open("lin.pl0");
	code =
		"const a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ofs << code;
	ofs.close();

	ofs.open("file01.pl0");
	code =
		"var x, squ;\n"
		"\n"
		"procedure square;\n"
		"begin\n"
		"	squ:= x * x\n"
		"end;\n"
		"\n"
		"begin\n"
		"	x := 1;\n"
		"	while x <= 10 do\n"
		"	begin\n"
		"		call square;\n"
		"		x := x + 1\n"
		"	end\n"
		"end.\n";
	ofs << code;
	ofs.close();

	ofs.open("file02.pl0");
	code =
		"const\n"
		"  m =  7,\n"
		"  n = 85;\n"
		" \n"
		"var\n"
		"  x, y, z, q, r;\n"
		" \n"
		"procedure multiply;\n"
		"var a, b;\n"
		" \n"
		"begin\n"
		"  a := x;\n"
		"  b := y;\n"
		"  z := 0;\n"
		"  while b > 0 do begin\n"
		"    if odd b then z := z + a;\n"
		"    a := 2 * a;\n"
		"    b := b / 2\n"
		"  end\n"
		"end;\n"
		" \n"
		"procedure divide;\n"
		"var w;\n"
		"begin\n"
		"  r := x;\n"
		"  q := 0;\n"
		"  w := y;\n"
		"  while w <= r do w := 2 * w;\n"
		"  while w > y do begin\n"
		"    q := 2 * q;\n"
		"    w := w / 2;\n"
		"    if w <= r then begin\n"
		"      r := r - w;\n"
		"      q := q + 1\n"
		"    end\n"
		"  end\n"
		"end;\n"
		" \n"
		"procedure gcd;\n"
		"var f, g;\n"
		"begin\n"
		"  f := x;\n"
		"  g := y;\n"
		"  while f # g do begin\n"
		"    if f < g then g := g - f;\n"
		"    if g < f then f := f - g\n"
		"  end;\n"
		"  z := f\n"
		"end;\n"
		" \n"
		"begin\n"
		"  x := m;\n"
		"  y := n;\n"
		"  call multiply;\n"
		"  x := 25;\n"
		"  y :=  3;\n"
		"  call divide;\n"
		"  x := 84;\n"
		"  y := 36;\n"
		"  call gcd\n"
		"end.\n";
	ofs << code;
	ofs.close();

	return RUN_ALL_TESTS();
}//main

