#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "sudoku.h"

// #define SIZE 9
#define GRIDSIZE 3


//

void updateboard(int i,int j,int k,int *** board)
{
	int p;
	for(p = 0; p < i; p++)
	{
		board[p][j][k] = 0;
	}
	for(p = i+1 ; p < SIZE ; p++)
	{
		board[p][j][k] = 0;
	}
	for(p = 0 ; p < j ; p++)
	{
		board[i][p][k] = 0;
	}
	for(p = j+1 ; p < SIZE ; p++)
	{
		board[i][p][k] = 0;
	}
	int gridno_i = i/GRIDSIZE;
	int gridno_j = j/GRIDSIZE;
	int l;
	for(p = gridno_i*GRIDSIZE ; p < gridno_i*(GRIDSIZE + 1) ; p++)
	{
		for(l = gridno_j*GRIDSIZE ; l < gridno_j*(GRIDSIZE + 1) ; l++)
		{
			board[p][l][k] = 0;
		}
	}
}

int *** eliminate(int*** board)
{
	
	// int i;
	// int repeat = 1;
	// //omp_set_num_threads(THREAD_NUM);
	// while(repeat == 1)
	// {
	// 	repeat = 0;
	// 	#pragma omp parallel for 
	// 	for(i = 0 ; i < SIZE ; i++)
	// 	{
	// 		int j,k;
	// 		for(j = 0 ; j < SIZE ; j++)
	// 		{
	// 			if(board[i][j][0] == 0)
	// 			{
	// 				int count = 0;
	// 				int t;
	// 				int p = 0;
	// 				for(k = 1 ; k <= SIZE ; k++)
	// 				{	
	// 					if(board[i][j][k] != 0)
	// 					{
	// 						if(count == 1)
	// 						{
	// 							p = 1;
	// 							break;
	// 						}
	// 						else
	// 						{
	// 							t = k;
	// 							count++;
	// 						}
	// 					}
	// 				}
	// 				if(p == 0)
	// 				{
	// 					repeat = 1;
	// 					board[i][j][0] = t;
	// 					updateboard(i,j,t,board);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	return board;
}

int *** loneranger(int ***board)
{	
	// int k;
	// int repeat = 1;
	// while(repeat == 1)
	// {
	// 	repeat = 0;
	
	// 	for(k = 1; k <= SIZE ; k++)
	// 	{
	// 		int i;
	// 		#pragma omp parallel for 
			
	// 			for(i = 0 ; i < SIZE ; i++)
	// 			{
	// 				int count = 0;
	// 				int t = 0;
	// 				int p = -1;
	// 				int r;
	// 				int j;
	// 				for(j = 0; j < SIZE ; j++)
	// 				{
	// 					if(board[i][j][0] == 0)
	// 					{
	// 						if(board[i][j][k] == 1)
	// 						{
	// 							if(count == 1)
	// 							{
	// 								p = 1;
	// 								break;
	// 							}
	// 							else
	// 							{
	// 								t = k;
	// 								r = j;
	// 								p = 0;
	// 								count += 1;
	// 							}
	// 						}
	// 					}
	// 				}
	// 				if(p == 0)
	// 				{
	// 					printf("here %d %d %d\n",i,j,t);
	// 					repeat = 1;
	// 					updateboard(i,r,t,board);
	// 					board[i][r][0] = t;
	// 				}

	// 			}
			
	// 		#pragma omp parallel for 
			
	// 			for(i = 0 ; i < SIZE ; i++)
	// 			{
	// 				int count = 0;
	// 				int t;
	// 				int p = -1;
	// 				int r;
	// 				int j;
	// 				for(j = 0; j < SIZE ; j++)
	// 				{
	// 					if(board[j][i][0] == 0)
	// 					{
	// 						if(board[j][i][k] == 1)
	// 						{
	// 							if(count == 1)
	// 							{
	// 								p = 1;
	// 								break;
	// 							}
	// 							else
	// 							{
	// 								t = k;
	// 								r = j;
	// 								p = 0;
	// 								count += 1;
	// 							}
	// 						}
	// 					}
	// 				}

	// 				if(p == 0)
	// 				{
	// 					printf("yoyoyo %d %d %d\n",r,i,t);
	// 					repeat = 1;
	// 					updateboard(r,i,t,board);
	// 					board[r][i][0] = t;
	// 				}
	// 			}
			
	// 		#pragma omp parallel for 
			
	// 			for(i = 0 ; i < SIZE ; i++)
	// 			{
	// 				int count = 0;
	// 				int t;
	// 				int u,r;
	// 				int j,l;
	// 				for(j = (i/GRIDSIZE)*(GRIDSIZE) ; j < (i/GRIDSIZE + 1)*(GRIDSIZE) ; j++)
	// 				{
	// 					for(l = (i%GRIDSIZE)*(GRIDSIZE) ; l < (i%GRIDSIZE + 1)*(GRIDSIZE) ; l++)
	// 					{
	// 						if((board[j][l][0] == 0))
	// 						{
	// 							if(board[j][l][k] == 1)
	// 							{
	// 								t = k;
	// 								u = j;
	// 								r = l;
	// 								count++;
	// 							}
	// 						}
	// 					}
	// 				}
	// 				if(count == 1)
	// 				{
	// 					printf("yahan pe %d %d %d \n",u,r,t);
	// 					repeat = 1;
	// 					updateboard(u,r,t,board);
	// 					board[u][r][0] = t;
	// 				}
	// 			}		
	// 	}
	// }

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