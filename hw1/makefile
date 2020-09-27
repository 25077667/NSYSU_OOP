FLAG = -O2 -g -Wall

all: dep
	gcc c/main.c stack_c.o ${FLAG} -o c_main.elf
	gcc c/main2.c stack_c.o ${FLAG} -o c_main2.elf
	g++ c++/main.cpp stack_cpp.o ${FLAG} -o cpp_main.elf
	g++ c++/main2.cpp stack_cpp.o ${FLAG} -o cpp_main2.elf

dep:
	gcc -c src/c/stack.c ${FLAG} -o stack_c.o
	g++ -c src/c++/stack.cpp ${FLAG} -o stack_cpp.o

clean:
	rm -f stack_c* *.elf

check:
	valgrind --verbose --leak-check=full --show-leak-kinds=all ./c_main.elf
	@echo "c_main.elf passed"
	valgrind --verbose --leak-check=full --show-leak-kinds=all ./c_main2.elf
	@echo "c_main2.elf passed"
	valgrind --verbose --leak-check=full --show-leak-kinds=all ./cpp_main.elf
	@echo "cpp_main.elf passed"
	valgrind --verbose --leak-check=full --show-leak-kinds=all ./cpp_main2.elf
	@echo "cpp_main2.elf passed"