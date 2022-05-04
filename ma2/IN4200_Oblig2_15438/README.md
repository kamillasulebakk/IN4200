# IN4200 Mandatory Assignment 2
## Denoising images

In this assignment we have implemented an algorithm for removing random noises in contaminated grey-scaled images in the JPEG format. In addition to write a serial program, we have also written a parallel implementation of the simple denoising algorithm, using MPI.


## The project is created with:
* C
  * stdlib.h
  * stdio.h
  * stdbool.h
  * mpi.h
  * time.h


## How to run serial program:
Open terminal window and enter the serial_code folder. The commando "make all" compiles the ready-made external C library package as well as the serial program with the denoising algorithm. In order to execute the program type "make run".

The following lines constitute the execution of the serial program as it stands in the makefile:
```
make run:
	./serial_main 0.1 200 ../img/noisy_mona_lisa.jpg ../img/denoised_mona_lisa_serial.jpg
```
Here;
* 0.1: is a small constant *κ*
* 200: is the number of iterations *iters* of the isotropic diffusion
* third argument: is the path of the input image `input_jpeg_filename`
* fourth argument: is to the path of the output image *output_jpeg_filename*

All command line arguments can of course be changed as desired. This can be done in the makefile or directly in the terminal window.

## How to run parallel program:
Open terminal window and enter the parallel_code folder. From here, the same procedure applies as for serial_code.

The following lines constitute the execution of the parallel program as it stands in the makefile:
```
make run:
	./parallel_main 0.1 200 ../img/noisy_mona_lisa.jpg ../img/denoised_mona_lisa_parallel.jpg
```
All command line arguments is the same as for serial_code.


## Files:
This project contains the following files:
* serial_code/serial_main.c
* serial_code/functions.c
* serial_code/functions.h
* parallel_code/parallel_main.c
* parallel_code/functions.c
* parallel_code/functions.h
* parallel_code/utils.c
* parallel_code/utils.h

## Output:
Below, we give the terminal output for both the serial and parallel program with command line arguments as listed above.

```
./serial_main 0.1 200 ../img/noisy_mona_lisa.jpg ../img/denoised_mona_lisa_serial.jpg

>> Succeeded! (H, W, C) = (4289, 2835, 1)
>> Program finished after: 26.646 seconds

./parallel_main 0.1 200 ../img/noisy_mona_lisa.jpg ../img/denoised_mona_lisa_parallel.jpg

>> Succeeded! (H, W, C) = (4289, 2835, 1)
>> Program finished after: 13.991 seconds



```
