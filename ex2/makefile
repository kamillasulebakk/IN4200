all: compile execute

compile:
	gcc ex2_3a.c -lm
	# to link math library:
	# gcc fname -lm

execute:
	valgrind --leak-check=yes ./a.out
