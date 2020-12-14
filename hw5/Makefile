CC=g++
FLAGS=-Wall -std=c++2a -O3 -Os

all: dep 
	$(CC) $(FLAGS) part1/*.[ch]* -o part1.elf
	$(CC) $(FLAGS) part2/Vector.h part2/main.cpp Trace.o -o part2.elf

dep: 
	$(CC) $(FLAGS) part2/Trace.cpp -c

check: all
	./part1.elf | diff -y part1/correct -
	./part2.elf 2>&1 | diff -y part2/correct -

clean:
	rm -rf *.o *.elf