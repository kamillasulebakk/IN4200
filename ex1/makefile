all: compile execute

compile:
	gcc ex1_2a.c -lm
	# to link math library:
	# gcc fname -lm

execute:
	valgrind --leak-check=yes ./a.out
