CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER g++-4.8)
# SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -march=native -flto -O3")
SET(CMAKE_CXX_FLAGS "-std=c++11 -g3 -gdwarf-2 -Wall -march=native")

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
# PROJECT
# --------------------------------------------------
PROJECT(PL0Compiler)
MESSAGE(STATUS "Project: " ${PROJECT_NAME})

SET(__TARGET_NAME__ homework/hw01)
SET(__SRC__
	homework/hw001.cpp
	src/filebuf/FileBuf.cpp
	src/tokenizer/Tokenizer.cpp
	src/tokenizer/WordMap.cpp
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})

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
	src/filebuf/FileBuf.cpp
	src/tokenizer/Tokenizer.cpp
	src/tokenizer/WordMap.cpp
)
ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
TARGET_LINK_LIBRARIES(${__TARGET_NAME__} gtest gtest_main pthread)
ADD_TEST(${__TEST_NAME__} ${__TARGET_NAME__})

# SET(__TEST_NAME__ test_Parser)
# SET(__TARGET_NAME__ test003_Parser)
# SET(__SRC__
# 	test/test003_Parser.cpp
# 	src/filebuf/FileBuf.cpp
# 	src/tokenizer/Tokenizer.cpp
# 	src/tokenizer/WordMap.cpp
# 	src/parser/detail/ConstVarDecl.cpp
# 	src/parser/detail/ConstDeclStmt.cpp
# 	src/parser/detail/VarDeclStmt.cpp
# )
# ADD_EXECUTABLE(${__TARGET_NAME__} ${__SRC__})
# TARGET_LINK_LIBRARIES(${__TARGET_NAME__} gtest gtest_main pthread)
# ADD_TEST(${__TEST_NAME__} ${__TARGET_NAME__})

