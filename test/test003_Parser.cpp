// STL
#include <iostream>
#include <memory>
#include <string>
// gtest
#include <gtest/gtest.h>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <tokenizer/Tokenizer.hpp>
#include <parser/all.hpp>

using namespace PL0;

TEST(ParserTest, Parse01) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("parser01.pl0");
	auto toker = std::make_shared<Tokenizer>(pfb, pwm);
	auto pp = auc::make_unique<Parser>();

	if(pp->parse(toker)) {
		SUCCEED();
	} else {
		FAIL();
	}//if-else
}

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);

	std::string code;
	std::ofstream ofs;

	ofs.open("parser01.pl0");
	code =
		"const a = 10;\n"
		"var b, c;\n"
		".\n";
	ofs << code;
	ofs.close();

	return RUN_ALL_TESTS();
}//main

