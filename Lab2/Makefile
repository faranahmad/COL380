

all: sudoku
	# ./sudoku 10 input25big.txt
	#./sudoku 10 sudoku16_input1
	# ./sudoku 1 sudoku9_input5
	./sudoku 10 inp36.txt

ts: ts.c sudoku.h
	gcc main.c ts.c -O3 -fopenmp -o ts

sudoku: sudoku.c sudoku.h
	gcc -Wall main.c sudoku.c -O3  -fopenmp -o sudoku

sudoku1: sudoku1.c sudoku.h
	gcc -Wall main.c sudoku1.c -O3 -fopenmp -o sudoku1

attempt2: attempt2.c sudoku.h
	gcc  main.c attempt2.c -O3 -fopenmp -o attempt2
	./attempt2 1 sudoku9_input1


debug: sudoku.c dancing.c
	gcc main.c dancing.c -g -fopenmp -o debug
	gdb debug

# sudoku: sudoku.c preprocess.c
# 	gcc main.c sudoku.c -O3 -fopenmp -o sudoku

# debug: sudoku.c 
# 	gcc -g main.c sudoku.c -fopenmp -o debug
# 	gdb debug

clean:
	rm -rf sudoku debug attempt2 
