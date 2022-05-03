# CC = mpicc
CC = /usr/lib64/openmpi/bin/mpicc
# executor = mpirun
executor = /usr/lib64/openmpi/bin/mpirun
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = parallel_main
OBJS = parallel_main.o functions.o ../serial_code/functions.o

DEP = functions.h ../serial_code/functions.h

all: simple-jpeg $(PROJ)

run:
	$(executor) -np 4 ./parallel_main 0.1 200

parallel_main: $(OBJS) $(DEP)
	$(CC) $(CFLAGS) *.c ../serial_code/functions.c -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

test:
	gcc tests/test_utils.c utils.c -o tests/test_utils
	tests/test_utils

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean
