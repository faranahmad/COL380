all: sudoku
	./sudoku 4 sudoku16_input4

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