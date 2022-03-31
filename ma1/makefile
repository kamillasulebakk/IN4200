execute: compile
	# ./a.out simple-webgraph.txt 1.00 1e-7 3
	# ./a.out 100-webgraph.txt 0.85 1e-6 3
	./a.out web-stanford.txt 0.85 1e-6 3

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c methods.c -Xpreprocessor -fopenmp -lomp