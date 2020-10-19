CC?=g++
FLAGS=-Wall -std=c++2a -Og -Os -g

all: dep
	$(CC) $(FLAGS) tar.o main.cpp -o mytar.elf

dep:
	$(CC) $(FLAGS) -c tar.c

clean:
	rm -rf tar.o mytar.elf