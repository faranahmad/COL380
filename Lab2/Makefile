all: sudoku
	./sudoku 2 f1.txt

sudoku: sudoku.c
	gcc main.c sudoku.c -O3 -fopenmp -o sudoku

debug: sudoku.c 
	gcc -g main.c sudoku.c -fopenmp -o debug
	gdb debug

clean:
	rm -rf sudoku debug 
