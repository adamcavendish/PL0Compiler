PL0Compiler
===========

A PL/0 Compiler written in c++11 [PL/0 on Wikipedia](http://en.wikipedia.org/wiki/PL/0)

PL/0 is a programming language used in our school's compiler principles course.

I am implementing the compiler using standard c++11 with gcc-4.8

----
Dependency:

* [cmake](http://www.cmake.org/)
* g++-4.8 or above

How to get cmake on Ubuntu:

	sudo apt-get install cmake

How to get g++-4.8 on Ubuntu:

	sudo add-apt-repository ppa:ubuntu-toolchain-r/test
	sudo apt-get update
	sudo apt-get install g++-4.8 c++-4.8

----
Build instructions:

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=RELEASE ..
	make -j

Build mode:

* DEBUG/RELEASE (use `-DCMAKE_BUILD_TYPE=DEBUG/RELEASE` to define)

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

	Parser
		::= ProgramUnit
	ProgramUnit
		::= BlockUnit "."
	BlockUnit
		::= [ConstDeclStmt] [VarDeclStmt] { ProcedureUnit } Statement
	ProcedureUnit
		::= ProcedureDecl BlockUnit ";"
	ConstDeclStmt
		::= "const" ConstVarDecl { "," ConstVarDecl } ";"
	VarDeclStmt
		::= "var" VarDecl { "," VarDecl } ";"
	ConstVarDecl
		::= ident "=" IntegerLiteral
	IntegerLiteral
		::= number
	VarDecl
		::= ident
	ProcedureDecl
		::= "procedure" ident ";"
	Statement
		::= CallStmt
		| CompoundStmt
		| IfStmt
		| WhileStmt
		| AssignStmt
	AssignStmt
		::= IdentRefExpression ":=" Expression
	CallStmt
		::=	"call" ProcedureRefExpression
	ProcedureRefExpression
		::= ident
	CompoundStmt
		::= "begin" Statement { ";" Statement } "end"
	IfStmt
		::= "if" CondStmt "then" Statement
	WhileStmt
		::= "while" CondStmt "do" Statement
	CondStmt
		::= "odd" Expression
		| Expression ("=" | "#" | "<" | "<=" | ">" | ">=") Expression
	Expression
		::= MultiplicativeExpression { ("+"|"-") MultiplicativeExpression }
	MultiplicativeExpression
		::= UnaryExpression { ("*"|"/") UnaryExpression }
	UnaryExpression
		::= ["+"|"-"] PrimaryExpression
	PrimaryExpression
		::= IdentRefExpression | IntegerLiteral | "(" Expression ")"
	IdentRefExpression
		::= ident

