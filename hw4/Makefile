CC=g++
FLAGS=-Wall -std=c++2a -O3 -Os

all: dep 
	$(CC) $(FLAGS) *.o driver/main.cpp -o main.elf

dep: lib/*.[ch]pp
	$(CC) $(FLAGS) -c lib/tag.cpp
	$(CC) $(FLAGS) -c lib/num.cpp
	$(CC) $(FLAGS) -c lib/op.cpp
	$(CC) $(FLAGS) -c lib/type.cpp
	$(CC) $(FLAGS) -c lib/token.cpp
	$(CC) $(FLAGS) -c lib/lexer.cpp

check: all
	@echo "test1"
	cat sample/test1 | ./main.elf > out1 2>&1
	diff out1 sample/test1.out
	@echo "test2"
	cat sample/test2 | ./main.elf > out2 2>&1
	diff out2 sample/test2.out

clean:
	rm -rf *.o *.elf out1 out2