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
}

TEST(TokenizerTest, chk_next) {
	std::size_t cnt = 0;

	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("win.pl0");

	Tokenizer toker(pfb, pwm);
	while(toker.next()) {
		std::cout << toker.token() << ": `" << toker.word() << "': <"
			<< toker.position().first << ", " << toker.position().second << ">"
			<< std::endl;
		++cnt;
		if(cnt > 30)
			break;
	}//while
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

	return RUN_ALL_TESTS();
}//main

