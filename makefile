#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: calc

# Tool invocations
# Executable "calculator" depends on the files calculator.o and run.o.
calc: calculator.o calc.o
	gcc -g -Wall -o calc calculator.o calc.o

# Depends on the source and header files
calculator.o: calculator.c
	gcc -g -Wall -c -o calculator.o calculator.c 
 
calc.o: calc.s
	nasm -g -f elf64 -w+all -o calc.o calc.s


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o calc
