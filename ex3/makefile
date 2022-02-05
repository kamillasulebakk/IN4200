all: compile execute

compile:
	gcc ex3_1.c -lm
	# to link math library:
	# gcc fname -lm

execute:
	valgrind --leak-check=yes ./a.out
