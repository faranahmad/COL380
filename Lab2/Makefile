all: sudoku
	# ./sudoku 10 input25big.txt
	./sudoku 10 sudoku16_input1

sudoku: sudoku.c sudoku.h
	gcc main.c sudoku.c -O3 -fopenmp -o sudoku

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