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

TEST(LLVMGenTest, Gen01) {
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
        if(pp->llvm_generate(context) != nullptr) {
            context->getModule_llvm()->dump();
            std::cout << "--------------------" << std::endl;
		    SUCCEED();
        } else {
            FAIL();
        }//if-else
	} else {
		pp->pretty_print(std::cout, 0);
		FAIL();
	}//if-else
}

/*
TEST(LLVMGenTest, Gen02) {
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

    SUCCEED();
	if(pp->parse(std::cout, context)) {
        pp->pretty_print(std::cout, 0);
        if(pp->llvm_generate(context) != nullptr) {
            context->getModule_llvm()->dump();
            std::cout << "--------------------" << std::endl;
		    SUCCEED();
        } else {
            FAIL();
        }//if-else
	} else {
		pp->pretty_print(std::cout, 0);
		FAIL();
	}//if-else
}
*/

/*
TEST(LLVMGenTest, Gen03) {
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
        if(pp->llvm_generate(context) != nullptr) {
            context->getModule_llvm()->dump();
            std::cout << "--------------------" << std::endl;
		    SUCCEED();
        } else {
            FAIL();
        }//if-else
		SUCCEED();
	} else {
		pp->pretty_print(std::cout, 0);
		FAIL();
	}//if-else
}
*/

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);

	std::string code;
	std::ofstream ofs;

	ofs.open("parser01.pl0");
	code =
		"const a = 10;\n"
		"var b, c;\n"
        "\n"
        "procedure check1;\n"
        "var dd;\n"
        "   procedure check2;\n"
        "   const cdd = 1024;\n"
        "   begin\n"
        "       dd := c\n"
        "   end;\n"
        "\n"
        "begin\n"
        "   dd := 1\n"
        "end;\n"
        "\n"
        "begin\n"
		"   b := -1024+53*(-514-766)/93+100;\n"
        "   c := b\n"
		"end.\n";
	ofs << code;
	ofs.close();

    ofs.open("parser02.pl0");
    code =
        "const a = 10;\n"
        "var b, c;\n"
        "\n"
        "procedure condcheck;\n"
        "begin\n"
        "   if odd b then\n"
        "       b := 100;\n"
        "   c := b\n"
        "end;\n"
        "\n"
        "begin\n"
        "   b := 1024;\n"
        "   call condcheck\n"
        "end.\n";
	ofs << code;
	ofs.close();

	ofs.open("parser03.pl0");
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

	ofs.open("parser04.pl0");
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

