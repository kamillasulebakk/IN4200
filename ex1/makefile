all: compile execute

compile:
	gcc ex1_1d.c
	# to link math library:
	# gcc fname -lm

execute:
	valgrind --leak-check=yes ./a.out
