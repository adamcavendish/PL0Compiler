// STL
#include <iostream>
#include <memory>
#include <string>
// auc
#include <auc/all.hpp>
// PL0Compiler
#include <filebuf/FileBuf.hpp>
#include <tokenizer/Tokenizer.hpp>
#include <parser/all.hpp>
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

	if(pp->parse(std::cout, toker)) {
		pp->pretty_print(std::cout, 0);
		std::cout << "Parse Succeeded!" << std::endl;
	} else {
		pp->pretty_print(std::cout, 0);
		std::cout << "Parse Failed!" << std::endl;
	}//if-else

	return 0;
}//main

