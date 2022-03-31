execute: compile
	# ./a.out data/simple-webgraph.txt 1.00 1e-7 3
	# ./a.out data/100-webgraph.txt 0.85 1e-6 3
	./a.out data/web-stanford.txt 0.85 1e-6 10

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c methods.c -Xpreprocessor -fopenmp -lomp