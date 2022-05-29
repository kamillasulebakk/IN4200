CC = /usr/lib64/openmpi/bin/mpicc
executor = /usr/lib64/openmpi/bin/mpirun
CFLAGS = -O2

run: parallel_main
	$(executor) -np 4 ./parallel_main

parallel_main:
	$(CC) $(CFLAGS) exam_2019_ex5.c  -o $@
