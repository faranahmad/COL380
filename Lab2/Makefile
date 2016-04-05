all: sudoku
	./sudoku 1 input25big.txt

sudoku: dancing.c sudoku.h
	gcc main.c dancing.c -O3 -fopenmp -o sudoku

debug: sudoku.c dancing.c
	gcc main.c dancing.c -g -fopenmp -o debug
	gdb debug

# sudoku: sudoku.c preprocess.c
# 	gcc main.c sudoku.c -O3 -fopenmp -o sudoku

# debug: sudoku.c 
# 	gcc -g main.c sudoku.c -fopenmp -o debug
# 	gdb debug

clean:
	rm -rf sudoku debug 