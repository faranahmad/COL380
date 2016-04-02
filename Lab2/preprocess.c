#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "sudoku.h"

// #define SIZE 9
#define GRIDSIZE 3


//

int *** eliminate(int*** board)
{
	
	int i;
	//omp_set_num_threads(THREAD_NUM);
	#pragma omp parallel for 
	for(i = 0 ; i < SIZE ; i++)
	{
		int j,k;
		for(j = 0 ; j < SIZE ; j++)
		{
			if(board[i][j][0] == 0)
			{
				int count = 0;
				int t;
				int p = 0;
				for(k = 1 ; k <= SIZE ; k++)
				{	
					if(board[i][j][k] != 0)
					{
						if(count == 1)
						{
							p = 1;
							break;
						}
						else
						{
							t = k;
							count++;
						}
					}
				}
				if(p == 0)
				{
					board[i][j][0] = t;
				}
			}
		}
	}
	return board;
}

int *** loneranger(int ***board)
{	
	int k;
	for(k = 1; k <= SIZE ; k++)
	{
		int i;
		#pragma omp parallel for 
		
			for(i = 0 ; i < SIZE ; i++)
			{
				int count = 0;
				int t = 0;
				int p = -1;
				int r;
				int j;
				for(j = 0; j < SIZE ; j++)
				{
					if(board[i][j][0] == 0)
					{
						if(board[i][j][k] == 1)
						{
							if(count == 1)
							{
								p = 1;
								break;
							}
							else
							{
								t = k;
								r = j;
								p = 0;
								count += 1;
							}
						}
					}
				}
				if(p == 0)
				{
					// printf("here %d %d %d\n",i,j,t);
					board[i][r][0] = t;
				}

			}
		
		#pragma omp parallel for 
		
			for(i = 0 ; i < SIZE ; i++)
			{
				int count = 0;
				int t;
				int p = -1;
				int r;
				int j;
				for(j = 0; j < SIZE ; j++)
				{
					if(board[j][i][0] == 0 || board[j][i][0] == k)
					{
						if(board[j][i][k] == 1)
						{
							if(count == 1)
							{
								p = 1;
								break;
							}
							else
							{
								t = k;
								r = j;
								p = 0;
								count += 1;
							}
						}
					}
				}

				if(p == 0)
				{
					// printf("yoyoyo %d %d %d\n",r,i,t);
					board[r][i][0] = t;
				}
			}
		
		#pragma omp parallel for 
		
			for(i = 0 ; i < SIZE ; i++)
			{
				int count = 0;
				int t;
				int u,r;
				int j,l;
				for(j = (i/GRIDSIZE)*(GRIDSIZE) ; j < (i/GRIDSIZE + 1)*(GRIDSIZE) ; j++)
				{
					for(l = (i%GRIDSIZE)*(GRIDSIZE) ; l < (i%GRIDSIZE + 1)*(GRIDSIZE) ; l++)
					{
						if((board[j][l][0] == 0) || (board[j][l][0]==k))
						{
							if(board[j][l][k] == 1)
							{
								t = k;
								u = j;
								r = l;
								count++;
							}
						}
					}
				}
				if(count == 1)
				{
					// printf("yahan pe %d %d %d \n",u,r,t);
					board[u][r][0] = t;
				}
			}
		
	}

	return board;
	
	
}




int ** FaranPart(int*** board)
{
	int *** board1 = eliminate(board);
	int *** board2 = loneranger(board1);
	int ** y = malloc(SIZE*sizeof(int*));
	int k;
    for (k=0; k<SIZE;k++)
    {
         y[k]=malloc(SIZE*sizeof(int));
    }
    int p,q;
    for(p = 0 ; p < SIZE ; p++)
    {
    	for(q = 0 ; q < SIZE ; q++)
    	{
    		y[p][q] = board2[p][q][0];
    	}
    }
    return y;
}