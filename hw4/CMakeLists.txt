project(main)
cmake_minimum_required(VERSION 3.12...3.20)

add_executable(main driver/main.cpp)
add_library(lex SHARED lib/tag.hpp lib/word.cpp lib/type.cpp lib/token.cpp lib/lexer.cpp lib/num.cpp)
set_property(TARGET lex PROPERTY CXX_STANDARD 20)
target_compile_features(main PUBLIC cxx_std_20)
target_link_libraries(main PUBLIC lex)