CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))
DEP = ex5.h

.PHONY : all clean

all: $(PROGRAMS)

ex5_2.exe : ex5_2.c $(DEP)
	$(CC) $< -o $@

ex5_3.exe : ex5_3.c $(DEP)
	$(CC) $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
