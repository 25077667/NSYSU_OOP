CC=g++
FLAGS=-Wall -std=c++2a -O3 -Os

all: dep 
	$(CC) $(FLAGS) part1/*.[ch]* -o part1.elf

dep: 

check: all
	./part1.elf | diff part1/correct -


clean:
	rm -rf *.o *.elf