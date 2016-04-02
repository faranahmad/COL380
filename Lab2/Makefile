all: sudoku
	./sudoku 2 f1.txt

sudoku: sudoku.c
	gcc main.c sudoku.c -O3 -fopenmp -o sudoku

clean:
	rm -rf sudoku
