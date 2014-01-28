CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#--------------------------------------------------
# Config-options
#--------------------------------------------------
# Compiler Stuffs
SET(CMAKE_CXX_COMPILER g++-4.8)
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -std=c++11 -Wall -march=native -flto -O3 ${CMAKE_CXX_FLAGS_RELEASE}")
SET(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g3 -gdwarf-2 -Wall -march=native ${CMAKE_CXX_FLAGS_DEBUG}")

# LLVM Stuffs
SET(LLVM_ROOT "/opt/llvm_optimized/" CACHE PATH "Root of LLVM install.")
INCLUDE_DIRECTORIES("${LLVM_ROOT}/include/")
LINK_DIRECTORIES("${LLVM_ROOT}/lib/")
SET(${LLVM_DEFINITIONS} -D_DEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS
	-D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
ADD_DEFINITIONS(${LLVM_DEFINITIONS})
SET(__LLVM_LINK_DEPEND__ dl curses pthread)
# same as `llvm-config --cppflags --ldflags --libs core`
SET(__LINK_LLVM_CORE__ LLVMCore LLVMSupport ${__LLVM_LINK_DEPEND__})
# same as `llvm-config --cppflags --ldflags --libs all`
SET(__LINK_LLVM_ALL__ 
	LLVMLTO LLVMObjCARCOpts LLVMLinker LLVMipo LLVMVectorize LLVMBitWriter
	LLVMIRReader LLVMBitReader LLVMAsmParser LLVMR600CodeGen LLVMR600Desc
	LLVMR600Info LLVMR600AsmPrinter LLVMSystemZDisassembler LLVMSystemZCodeGen
	LLVMSystemZAsmParser LLVMSystemZDesc LLVMSystemZInfo LLVMSystemZAsmPrinter
	LLVMHexagonCodeGen LLVMHexagonAsmPrinter LLVMHexagonDesc LLVMHexagonInfo 
	LLVMNVPTXCodeGen LLVMNVPTXDesc LLVMNVPTXInfo LLVMNVPTXAsmPrinter
	LLVMCppBackendCodeGen LLVMCppBackendInfo LLVMMSP430CodeGen LLVMMSP430Desc
	LLVMMSP430Info LLVMMSP430AsmPrinter LLVMXCoreDisassembler LLVMXCoreCodeGen
	LLVMXCoreDesc LLVMXCoreInfo LLVMXCoreAsmPrinter LLVMMipsDisassembler
	LLVMMipsCodeGen LLVMMipsAsmParser LLVMMipsDesc LLVMMipsInfo LLVMMipsAsmPrinter
	LLVMARMDisassembler LLVMARMCodeGen LLVMARMAsmParser LLVMARMDesc LLVMARMInfo
	LLVMARMAsmPrinter LLVMAArch64Disassembler LLVMAArch64CodeGen LLVMAArch64AsmParser
	LLVMAArch64Desc LLVMAArch64Info LLVMAArch64AsmPrinter LLVMAArch64Utils
	LLVMPowerPCDisassembler LLVMPowerPCCodeGen LLVMPowerPCAsmParser LLVMPowerPCDesc
	LLVMPowerPCInfo LLVMPowerPCAsmPrinter LLVMSparcDisassembler LLVMSparcCodeGen
	LLVMSparcAsmParser LLVMSparcDesc LLVMSparcInfo LLVMSparcAsmPrinter LLVMTableGen
	LLVMDebugInfo LLVMOption LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen
	LLVMSelectionDAG LLVMAsmPrinter LLVMMCParser LLVMX86Desc LLVMX86Info LLVMX86AsmPrinter
	LLVMX86Utils LLVMJIT LLVMMCDisassembler LLVMInstrumentation LLVMInterpreter LLVMCodeGen
	LLVMScalarOpts LLVMInstCombine LLVMTransformUtils LLVMipa LLVMAnalysis LLVMMCJIT 
	LLVMTarget LLVMRuntimeDyld LLVMExecutionEngine LLVMMC LLVMObject LLVMCore LLVMSupport
	${__LLVM_LINK_DEPEND__}
)

# --------------------------------------------------
# Add gtest
# --------------------------------------------------
INCLUDE(ExternalProject)
# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
ExternalProject_Add(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    SVN_REVISION -r 660
    TIMEOUT 1
	# Disable update step
	UPDATE_COMMAND ""
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)
# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES("${source_dir}/include/")
ExternalProject_Get_Property(googletest binary_dir)
LINK_DIRECTORIES("${binary_dir}/")
# --------------------------------------------------
# Add gtest fin.
# --------------------------------------------------

ENABLE_TESTING()
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include/")

FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/homework/")

# --------------------------------------------------
# Dependencies
# --------------------------------------------------
SET(__SRC_TOKENIZER__
	src/filebuf/FileBuf.cpp
	src/tokenizer/Tokenizer.cpp
	src/tokenizer/WordMap.cpp
)

SET(__SRC_PARSER__
	src/parser/HelperFunctions.cpp
	src/parser/Parser.cpp
	src/parser/detail/AssignStmt.cpp
	src/parser/detail/BlockUnit.cpp
	src/parser/detail/CallStmt.cpp
	src/parser/detail/CompoundStmt.cpp
	src/parser/detail/CondStmt.cpp
	src/parser/detail/ConstDeclStmt.cpp
	src/parser/detail/ConstVarDecl.cpp
	src/parser/detail/Expression.cpp
	src/parser/detail/FunctionRefExpression.cpp
	src/parser/detail/IdentRefExpression.cpp
	src/parser/detail/IfStmt.cpp
	src/parser/detail/IntegerLiteral.cpp
	src/parser/detail/MultiplicativeExpression.cpp
	src/parser/detail/PrimaryExpression.cpp
	src/parser/detail/ProcedureDecl.cpp
	src/parser/detail/ProcedureRefExpression.cpp
	src/parser/detail/ProcedureUnit.cpp
	src/parser/detail/ProgramUnit.cpp
	src/parser/detail/Statement.cpp
	src/parser/detail/UnaryExpression.cpp
	src/parser/detail/VarDecl.cpp
	src/parser/detail/VarDeclStmt.cpp
	src/parser/detail/WhileStmt.cpp
)

SET(__SRC_LLVM_SYMTABLE__
	src/symtable/SymTable_llvm.cpp
)

SET(__SRC_SYMTABLE__
	src/symtable/SymTable.cpp
)

SET(__SRC_CONTEXT__
	src/context/Context.cpp
)

# --------------------------------------------------
# PROJECT
# --------------------------------------------------
PROJECT(PL0Compiler)
MESSAGE(STATUS "Project: " ${PROJECT_NAME})

SET(__TARGET_NAME__ homework/hw001)
SET(__SRC__
	homework/hw001.cpp
	${__SRC_TOKENIZER__}
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})

SET(__TARGET_NAME__ homework/hw002)
SET(__SRC__
	homework/hw002.cpp
	${__SRC_TOKENIZER__}
	${__SRC_PARSER__}
	${__SRC_LLVM_SYMTABLE__}
	${__SRC_CONTEXT__}
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(${__TARGET_NAME__} ${__LINK_LLVM_CORE__})

# --------------------------------------------------
# TESTS
# --------------------------------------------------
SET(__TEST_NAME__ test_FileBuf)
SET(__TARGET_NAME__ test001_FileBuf)
SET(__SRC__
	test/test001_FileBuf.cpp
	src/filebuf/FileBuf.cpp
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(${__TARGET_NAME__} gtest gtest_main pthread)
ADD_TEST(${__TEST_NAME__} ${__TARGET_NAME__})

SET(__TEST_NAME__ test_Tokenizer)
SET(__TARGET_NAME__ test002_Tokenizer)
SET(__SRC__
	test/test002_Tokenizer.cpp
	${__SRC_TOKENIZER__}
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(${__TARGET_NAME__} gtest gtest_main pthread)
ADD_TEST(${__TEST_NAME__} ${__TARGET_NAME__})

SET(__TEST_NAME__ test_Parser)
SET(__TARGET_NAME__ test003_Parser)
SET(__SRC__
	test/test003_Parser.cpp
	${__SRC_TOKENIZER__}
	${__SRC_PARSER__}
	${__SRC_LLVM_SYMTABLE__}
	${__SRC_CONTEXT__}
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(${__TARGET_NAME__} gtest gtest_main pthread ${__LINK_LLVM_CORE__})
ADD_TEST(${__TEST_NAME__} ${__TARGET_NAME__})

