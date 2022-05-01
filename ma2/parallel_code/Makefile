CC = mpicc
# CC = gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = parallel_main
OBJS = parallel_main.o functions.o

DEP = functions.h

all: simple-jpeg $(PROJ)

parallel_main: $(OBJS) $(DEP)
	$(CC) $(CFLAGS) *.c -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

test:
	gcc test_utils.c utils.c -o test_utils
	./test_utils

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
