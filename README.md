PL0Compiler
===========

A PL/0 Compiler written in c++11 [PL/0 on Wikipedia](http://en.wikipedia.org/wiki/PL/0)

PL/0 is a programming language used in our school's compiler principles course.

I am implementing the compiler using standard c++11 with gcc-4.8

----
Dependency:

* [cmake](http://www.cmake.org/)

----

## Grammar

The following is the syntax rules of the model language defined in EBNF:

	program = block "."

	block = [ "const" ident "=" number { "," ident "=" number } ";" ]
			[ "var" ident { "," ident } ";" ]
			{ "procedure" ident ";" block ";" } statement

	statement = [ ident ":=" expression | "call" ident |
				"begin" statement { ";" statement } "end" |
				"if" condition "then" statement |
				"while" condition "do" statement ]

	condition = "odd" expression |
				expression ("="|"#"|"<"|"<="|">"|">=") expression

	expression = ["+"|"-"] term { ("+"|"-") term }

	term = factor { ("*"|"/") factor }

	factor = ident | number | "(" expression ")"

----

## Abstruct-Syntax-Tree Structure

Parser structure:

	Parser ::=
		ProgramUnit
	ProgramUnit ::=
		BlockUnit "."
	BlockUnit ::=
		[ConstDeclStmt] [VarDeclStmt]
	ConstDeclStmt ::=
		"const" ConstVarDecl { "," ConstVarDecl } ";"
	VarDeclStmt ::=
		"var" VarDecl { "," VarDecl } ";"
	ConstVarDecl ::=
		ident "=" number
	VarDecl ::=
		ident

