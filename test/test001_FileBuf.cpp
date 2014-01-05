// STL
#include <iostream>
#include <string>
// gtest
#include <gtest/gtest.h>
// PL0Compiler
#include <filebuf/FileBuf.hpp>

using namespace PL0;

TEST(FileBufTest, chk_constructor) {
	FileBuf fb("win.pl0");
	SUCCEED();
}

TEST(FileBufTest, chk_get) {
	FileBuf fb("win.pl0");

	std::string code;
	char ch = fb.get();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;

		fb.bump();
		ch = fb.get();
	}//while

	std::string expect =
		"const a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";

	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_win_bump) {
	FileBuf fb("win.pl0");

	std::string code;
	char ch = fb.bump();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.bump();
	}//while

	std::string expect = 
		"const a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_mac_bump) {
	FileBuf fb("mac.pl0");

	std::string code;
	char ch = fb.bump();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.bump();
	}//while

	std::string expect = 
		"const a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_lin_bump) {
	FileBuf fb("lin.pl0");

	std::string code;
	char ch = fb.bump();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.bump();
	}//while

	std::string expect = 
		"const a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_win_next) {
	FileBuf fb("win.pl0");

	std::string code;
	char ch = fb.next();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.next();
	}//while

	std::string expect = 
		"onst a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_mac_next) {
	FileBuf fb("mac.pl0");

	std::string code;
	char ch = fb.next();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.next();
	}//while

	std::string expect = 
		"onst a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_lin_next) {
	FileBuf fb("lin.pl0");

	std::string code;
	char ch = fb.next();
	while(ch != std::char_traits<char>::eof()) {
		code += ch;
		ch = fb.next();
	}//while

	std::string expect = 
		"onst a=10;\n"
		"var b,c;\n"
		"begin\n"
		"read(b);\n"
		"c:=a+b;\n"
		"write(c);\n"
		"end.\n"
		"\n";
	ASSERT_EQ(expect, code);
}

TEST(FileBufTest, chk_unget) {
	FileBuf fb("win.pl0");

	char ch = fb.bump();
	fb.unget();

	ASSERT_EQ(ch, fb.get());
}

TEST(FileBufTest, chk_line_position) {
	FileBuf fb("win.pl0");
	char ch = fb.get();

	ASSERT_EQ(ch, 'c');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 1);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'o');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 2);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'n');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 3);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 's');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 4);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 't');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 5);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, ' ');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 6);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'a');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 7);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, '=');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 8);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, '1');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 9);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, '0');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 10);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, ';');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 11);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, '\n');
	ASSERT_EQ(fb.line(), 1);
	ASSERT_EQ(fb.position(), 12);
	fb.bump();
	
	ch = fb.get();
	ASSERT_EQ(ch, 'v');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 1);
	fb.bump();
	
	ch = fb.get();
	ASSERT_EQ(ch, 'a');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 2);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'r');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 3);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, ' ');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 4);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'b');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 5);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, ',');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 6);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, 'c');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 7);
	fb.bump();

	ch = fb.get();
	ASSERT_EQ(ch, ';');
	ASSERT_EQ(fb.line(), 2);
	ASSERT_EQ(fb.position(), 8);
	fb.bump();

	SUCCEED();
}

TEST(FileBufTest, chk_next_at_newline) {
	FileBuf fb("win.pl0");

	char ch;
	for(auto i = 0; i < 11; ++i)
		fb.bump();
	ch = fb.next();

	ASSERT_EQ(ch, 'v');
	EXPECT_EQ(fb.line(), 2);
	EXPECT_EQ(fb.position(), 1);
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

