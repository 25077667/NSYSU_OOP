CC=g++
FLAGS=-Wall -std=c++2a -O3 -Os

all: dep 
	$(CC) $(FLAGS) *.o driver/main.cpp -o main.elf

dep: lib/*.[ch]pp
	$(CC) $(FLAGS) -c lib/tag.cpp
	$(CC) $(FLAGS) -c lib/word.cpp
	$(CC) $(FLAGS) -c lib/type.cpp
	$(CC) $(FLAGS) -c lib/token.cpp
	$(CC) $(FLAGS) -c lib/lexer.cpp

clean:
	rm -rf *.o *.elf