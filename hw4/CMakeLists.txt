project(Lexer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Ofast)
add_executable(main.elf lib/lexer.cpp lib/num.cpp lib/op.cpp lib/tag.cpp lib/token.cpp lib/type.cpp lib/word.cpp driver/main.cpp)