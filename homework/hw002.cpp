// STL
#include <iostream>
#include <memory>
#include <string>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <filebuf/FileBuf.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <symtable/SymTable_llvm.hpp>
#include <context/Context.hpp>
#include <parser/all.hpp>
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
using namespace PL0;

int main(int argc, char * argv[]) {
	if(argc != 2) {
		std::cout << "Usage: " << argv[0] << " file_to_parse" << std::endl;
		return 1;
	}//if

	auto pwm = std::make_shared<WordMap>();
	auto pfb = std::make_shared<FileBuf>(argv[1]);
	if(!pfb->ok()) {
		std::cout << "Open file error!" << std::endl;
		return 1;
	}//if
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
		std::cout << "Parse Succeeded!" << std::endl;
	} else {
		pp->pretty_print(std::cout, 0);
		std::cout << "Parse Failed!" << std::endl;
	}//if-else

	return 0;
}//main

