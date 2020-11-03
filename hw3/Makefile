CC=g++
FLAGS=-Wall -std=c++2a -Og -Os -g

all: dep 
	$(CC) $(FLAGS) Complex.o main.cpp -o main.elf

dep:
	$(CC) $(FLAGS) -c Complex.cpp

clean:
	rm -rf *.o *.elf