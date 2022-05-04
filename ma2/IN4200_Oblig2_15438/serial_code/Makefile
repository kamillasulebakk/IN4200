CC = gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
OBJS = serial_main.o functions.o

DEP = functions.h

all: simple-jpeg $(PROJ)

run:
	./serial_main 0.1 200 ../img/noisy_mona_lisa.jpg ../img/denoised_mona_lisa_serial.jpg 

serial_main: $(OBJS) $(DEP)
	$(CC) $(CFLAGS) *.c -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

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
