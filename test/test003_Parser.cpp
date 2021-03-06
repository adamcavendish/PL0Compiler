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
#include <symtable/SymTable_llvm.hpp>
#include <context/Context.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

using namespace PL0;

TEST(ParserTest, Parse01) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("parser01.pl0");
	auto toker = std::make_shared<Tokenizer>(pfb, pwm);
	auto pp = auc::make_unique<Parser>();

	auto llvmsymtable = std::make_shared<SymTable_llvm>();
	auto llvmcontext = std::make_shared<llvm::LLVMContext>();
	auto llvmmodule = std::make_shared<llvm::Module>("LLVM Module", *(llvmcontext.get()));
	auto llvmbuilder = std::make_shared<llvm::IRBuilder<>>(*(llvmcontext.get()));
	auto context = std::make_shared<Context>(
			toker, nullptr, llvmsymtable, llvmcontext, llvmmodule, llvmbuilder);

	if(pp->parse(std::cout, context)) {
		pp->pretty_print(std::cout, 0);
		SUCCEED();
	} else {
		pp->pretty_print(std::cout, 0);
		FAIL();
	}//if-else
}

TEST(ParserTest, Parser02) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("parser02.pl0");
	auto toker = std::make_shared<Tokenizer>(pfb, pwm);
	auto pp = auc::make_unique<Parser>();

	auto llvmsymtable = std::make_shared<SymTable_llvm>();
	auto llvmcontext = std::make_shared<llvm::LLVMContext>();
	auto llvmmodule = std::make_shared<llvm::Module>("LLVM Module", *(llvmcontext.get()));
	auto llvmbuilder = std::make_shared<llvm::IRBuilder<>>(*(llvmcontext.get()));
	auto context = std::make_shared<Context>(
			toker, nullptr, llvmsymtable, llvmcontext, llvmmodule, llvmbuilder);

	if(pp->parse(std::cout, context)) {
		pp->pretty_print(std::cout, 0);
		SUCCEED();
	} else {
		pp->pretty_print(std::cout, 0);
		FAIL();
	}//if-else
}

TEST(ParserTest, Parser03) {
	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>("parser03.pl0");
	auto toker = std::make_shared<Tokenizer>(pfb, pwm);
	auto pp = auc::make_unique<Parser>();

	auto llvmsymtable = std::make_shared<SymTable_llvm>();
	auto llvmcontext = std::make_shared<llvm::LLVMContext>();
	auto llvmmodule = std::make_shared<llvm::Module>("LLVM Module", *(llvmcontext.get()));
	auto llvmbuilder = std::make_shared<llvm::IRBuilder<>>(*(llvmcontext.get()));
	auto context = std::make_shared<Context>(
			toker, nullptr, llvmsymtable, llvmcontext, llvmmodule, llvmbuilder);

	if(pp->parse(std::cout, context)) {
		pp->pretty_print(std::cout, 0);
		SUCCEED();
	} else {
		pp->pretty_print(std::cout, 0);
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
		"b := -1024+53*(-514-766)/93+100\n"
		".\n";
	ofs << code;
	ofs.close();

	ofs.open("parser02.pl0");
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

	ofs.open("parser03.pl0");
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

