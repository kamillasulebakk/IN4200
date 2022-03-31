# IN4200 Mandatory Assignment 1
## Computing PageRank

In this assignment we have red a text file that contains a web graph, so that the corresponding hyperlink matrix is built up in CRS format. Further we have calculated the PageRank scores for each webpage and parallelized the code using OpenMP.


## The project is created with:
* C
  * stdlib.h
  * stdio.h
  * omp.h
  * time.h


## How to run the code:
Open terminal window and type "make". This command compile and execute all programs.

The following lines constitute the makefile:
```
execute: compile
	./a.out data/web-stanford.txt 0.85 1e-6 10

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c methods.c -Xpreprocessor -fopenmp -lomp
```
Here;
* web-stanford.txt: corresponds to the filename of a web graph file
* 0.85: corresponds to the damping constant *d*
* 1e-6: corresponds to the convergence threshold value *ε*
* 10: corresponds to the value of *n* related to showing the top 10 webpages

These command line arguments can of course be changed as desired. This is done in the makefile.


## Files:
This project contains the following 6 files:
* main.c
* read_graph_from_file.c
* PageRank_iterations.c
* top_n_webpages.c
* methods.h
* methods.c

Here;
* main.c, contains a main program that initializes needed pointers and accepts, on the command line, the filename, *d*, *ε* and *n*. Further, the main program calls the three functions: read_graph_from_file, PageRank_iterations and top_n_webpages.

* read_graph_from_file.c, contains the function read_graph_from_file that allocates needed pointers and reads a text file that contains a web graph. The  corresponding hyperlink matrix of the web graph is built up in CRS format.

* PageRank_iterations.c, contains the function PageRank_iterations that implements the iterative procedure of the PageRank algorithm. The computed PageRank scores are stored in a pre-allocated 1D array.

* top_n_webpages.c, contains the function top_n_webpages that goes through the computed PageRank score vector and prints out the top *n* webpages, with both their scores and webpage indices.

* methods.h declares functions that are widely used by the "main programs".

* methods.c, contains different functions that are used many times.


## Output:
Below, we give the terminal output for the command line arguments listed above. These results have been produced using gcc version 13.0.

```
./a.out data/web-stanford.txt 0.85 1e-6 10

Excluding 0 invalid entries

Running program with 281903 nodes

read_graph_from_file finished in 0.501890 s

Number of dangling nodes 173

Number of iterations until convergence: 41

PageRank_iterations finished in 0.219164 s

Indices of top 10 webpages:
(89073, 226411, 241454, 262860, 134832, 234704, 136821, 68889, 105607, 69358)

Scores in decreasing order:
(0.011303, 0.009268, 0.008298, 0.003023, 0.003001, 0.002572, 0.002454, 0.002431, 0.002391, 0.002364)

top_n_webpages finished in 0.002053 s
```