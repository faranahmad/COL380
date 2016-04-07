<<<<<<< HEAD
all: sudoku 
	./sudoku 1 sudoku9_input5
=======
all: sudoku
	# ./sudoku 10 input25big.txt
	#./sudoku 10 sudoku16_input1
	./sudoku 10 input25big.txt
>>>>>>> c7326b6675a48278f59df7db3f39dc5f50b6bb0a

sudoku: sudoku.c sudoku.h
	gcc -Wall main.c sudoku.c -O3 -fopenmp -o sudoku

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
