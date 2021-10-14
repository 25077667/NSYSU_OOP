FLAG = -Ofast -Wall

all: dep
	gcc c/main.c stack_c.o ${FLAG} -o c_main.elf
	gcc c/main2.c stack_c.o ${FLAG} -o c_main2.elf
	gcc c/driver.c stack_c.o ${FLAG} -o special_driver.elf
	g++ c++/main.cpp stack_cpp.o stack_c.o ${FLAG} -o cpp_main.elf
	g++ c++/main2.cpp stack_cpp.o stack_c.o ${FLAG} -o cpp_main2.elf
	strip special_driver.elf

dep:
	gcc -c src/c/stack.c ${FLAG} -L -fPIC -shared -o stack_c.o
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

summay_check:
	valgrind ./c_main.elf 1>/dev/null
	valgrind ./c_main2.elf 1>/dev/null
	valgrind ./cpp_main.elf 1>/dev/null
	valgrind ./cpp_main2.elf 1>/dev/null