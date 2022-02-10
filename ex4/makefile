all: compile execute

compile:
	gcc ex4_3.c -lm
	# to link math library:
	# gcc fname -lm

execute:
	valgrind --leak-check=yes ./a.out
