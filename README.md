PL0Compiler
===========

A PL/0 Compiler written in c++11 [PL/0 on Wikipedia](http://en.wikipedia.org/wiki/PL/0)

PL/0 is a programming language used in our school's compiler principles course.

I am implementing the compiler using standard c++11 with gcc-4.8

----
Dependency:

* [gtest-1.7.0](https://code.google.com/p/googletest/)
> Download **gtest-1.7.0** and unpack it in the **external** directory
> if you get **external/gtest-1.7.0/** that means you're getting it right
> cd external/gtest-1.7.0
> ./configure
> make

----
The following is the syntax rules of the model language defined in EBNF:

	program = block "." .

	block = [ "const" ident "=" number {"," ident "=" number} ";"]
			[ "var" ident {"," ident} ";"]
			{ "procedure" ident ";" block ";" } statement .

	statement = [ ident ":=" expression | "call" ident |
				"begin" statement {";" statement } "end" |
				"if" condition "then" statement |
				"while" condition "do" statement ].

	condition = "odd" expression |
				expression ("="|"#"|"<"|"<="|">"|">=") expression .

	expression = [ "+"|"-"] term { ("+"|"-") term}.

	term = factor {("*"|"/") factor}.

	factor = ident | number | "(" expression ")".

