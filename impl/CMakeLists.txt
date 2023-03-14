project(ECC)

cmake_minimum_required(VERSION 3.12)

# Find dependencies: Parser
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(ECC_LEXER ${CMAKE_SOURCE_DIR}/src/lexer.l
  ${CMAKE_SOURCE_DIR}/src/generated/lexer.yy.cc)

BISON_TARGET(ECC_PARSER ${CMAKE_SOURCE_DIR}/src/parser.y
  ${CMAKE_SOURCE_DIR}/src/generated/parser.tab.cc)

ADD_FLEX_BISON_DEPENDENCY(ECC_LEXER ECC_PARSER)

file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.cc)

# Build the main function.
add_executable(ecc
  ${SRCS}
  ${FLEX_ECC_LEXER_OUTPUTS}
  ${BISON_ECC_PARSER_OUTPUTS})

target_include_directories(ecc PRIVATE ${CMAKE_SOURCE_DIR}/include)
