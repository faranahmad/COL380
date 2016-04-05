#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "sudoku.h"

// #define SIZE 9
<<<<<<< HEAD

=======
>>>>>>> 35adb7ea7f794eeacbdb70d36a7e473ab69d545a
#define GRIDSIZE MINIGRIDSIZE


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
	for(p = gridno_i*GRIDSIZE ; p < (gridno_i+1)*(GRIDSIZE) ; p++)
	{
		for(l = gridno_j*GRIDSIZE ; l < (gridno_j+1)*(GRIDSIZE) ; l++)
		{
			board[p][l][k] = 0;
		}
	}
}

int *** eliminate(int*** board)
{

	int i;
	int repeat = 1;
	//omp_set_num_threads(THREAD_NUM);
	while(repeat == 1)
	{
		repeat = 0;
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
						repeat = 1;
						board[i][j][0] = t;
						updateboard(i,j,t,board);
					}
				}
			}
		}
	}
	return board;
}

<<<<<<< HEAD
// cdint *** loneranger(int ***board)
// {	
// 	int k;
// 	int repeat = 1;
// 	while(repeat == 1)
// 	{
// 		repeat = 0;
	
// 		for(k = 1; k <= SIZE ; k++)
// 		{
// 			int i;
// 			#pragma omp parallel for 
			
// 				for(i = 0 ; i < SIZE ; i++)
// 				{
// 					int count = 0;
// 					int t = 0;
// 					int p = -1;
// 					int r;
// 					int j;
// 					for(j = 0; j < SIZE ; j++)
// 					{
// 						if(board[i][j][0] == 0)
// 						{
// 							if(board[i][j][k] == 1)
// 							{
// 								if(count == 1)
// 								{
// 									p = 1;
// 									break;
// 								}
// 								else
// 								{
// 									t = k;
// 									r = j;
// 									p = 0;
// 									count += 1;
// 								}
// 							}
// 						}
// 					}
// 					if(p == 0)
// 					{
// 						// printf("here %d %d %d\n",i,j,t);
// 						repeat = 1;
// 						updateboard(i,r,t,board);
// 						board[i][r][0] = t;
// 					}

// 				}
			
// 			#pragma omp parallel for 
			
// 				for(i = 0 ; i < SIZE ; i++)
// 				{
// 					int count = 0;
// 					int t;
// 					int p = -1;
// 					int r;
// 					int j;
// 					for(j = 0; j < SIZE ; j++)
// 					{
// 						if(board[j][i][0] == 0)
// 						{
// 							if(board[j][i][k] == 1)
// 							{
// 								if(count == 1)
// 								{
// 									p = 1;
// 									break;
// 								}
// 								else
// 								{
// 									t = k;
// 									r = j;
// 									p = 0;
// 									count += 1;
// 								}
// 							}
// 						}
// 					}

// 					if(p == 0)
// 					{
// 						// printf("yoyoyo %d %d %d\n",r,i,t);
// 						repeat = 1;
// 						updateboard(r,i,t,board);
// 						board[r][i][0] = t;
// 					}
// 				}
			
// 			#pragma omp parallel for 
			
// 				for(i = 0 ; i < SIZE ; i++)
// 				{
// 					int count = 0;
// 					int t;
// 					int u,r;
// 					int j,l;
// 					for(j = (i/GRIDSIZE)*(GRIDSIZE) ; j < (i/GRIDSIZE + 1)*(GRIDSIZE) ; j++)
// 					{
// 						for(l = (i%GRIDSIZE)*(GRIDSIZE) ; l < (i%GRIDSIZE + 1)*(GRIDSIZE) ; l++)
// 						{
// 							if((board[j][l][0] == 0))
// 							{
// 								if(board[j][l][k] == 1)
// 								{
// 									t = k;
// 									u = j;
// 									r = l;
// 									count++;
// 								}
// 							}
// 						}
// 					}
// 					if(count == 1)
// 					{
// 						// printf("yahan pe %d %d %d \n",u,r,t);
// 						repeat = 1;
// 						updateboard(u,r,t,board);
// 						board[u][r][0] = t;
// 					}
// 				}		
// 		}
// 	}

// 	return board;
	
	
// }


int *** loneranger(int *** board)
{
	// int repeat = 1;
	// while(repeat == 1)
	// {
	// 	repeat = 0;
	// 	int i;
	// 	#pragma omp parallel for
	// 	for(i = 0;i < 3*SIZE;i++)
	// 	{
	// 		if(i < SIZE)
	// 		{
	// 			int j,l,k;
	// 			// for(j = (i/GRIDSIZE)*GRIDSIZE;j < (i/GRIDSIZE+1)*GRIDSIZE;j++)
	// 			// {
	// 			// 	for(l = (i%GRIDSIZE)*GRIDSIZE;l < (i%GRIDSIZE + 1)*GRIDSIZE;l++)
	// 			// 	{
	// 					for(k = 1;k <= 10;k++)
	// 					{
	// 						int t,u,r,j1,l1;
	// 						int count = 0;
	// 						for(j1 = (i/GRIDSIZE)*(GRIDSIZE) ; j1 < (i/GRIDSIZE + 1)*(GRIDSIZE) ; j1++)
	// 						{	
	// 							for(l1 = (i%GRIDSIZE)*(GRIDSIZE) ; l1 < (i%GRIDSIZE + 1)*(GRIDSIZE) ; l1++)
	// 							{
	// 								if((board[j1][l1][0] == 0))
	// 								{
	// 									if(board[j1][l1][k] == 1)
	// 									{
	// 										t = k;
	// 										u = j1;
	// 										r = l1;
	// 										count++;
	// 									}
	// 								}
	// 							}
	// 						}
	// 						if(count == 1)
	// 						{
	// 							// printf("yahan pe %d %d %d \n",u,r,t);
	// 							repeat = 1;
	// 							updateboard(u,r,t,board);
	// 							board[u][r][0] = t;
	// 						}		
	// 				// 	}
	// 				// }
	// 			}
	// 			printf("yahan pe done till here \n");
	// 		}
	// 		else if(i < 2*SIZE)
	// 		{
	// 			int k;
	// 			for(k = 1;k <=10;k++)
	// 			{
	// 				int count = 0;
	// 				int t = 0;
	// 				int p = -1;
	// 				int r;
	// 				int j;
	// 				for(j = 0; j < SIZE ; j++)
	// 				{
	// 					if(board[i-SIZE][j][0] == 0)
	// 					{
	// 						if(board[i-SIZE][j][k] == 1)
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
	// 					// printf("here %d %d %d\n",i,j,t);
	// 					repeat = 1;
	// 					updateboard(i-SIZE,r,t,board);
	// 					board[i-SIZE][r][0] = t;
	// 				}
	// 			}
	// 			printf("yahan pe done till here 2 \n");	
	// 		}
	// 		else
	// 		{
	// 			int k;
	// 			for(k = 1;k <= 10 ;k++)
	// 			{
	// 				int count = 0;
	// 				int t;
	// 				int p = -1;
	// 				int r;
	// 				int j;
	// 				for(j = 0; j < SIZE ; j++)
	// 				{
	// 					if(board[j][i-2*SIZE][0] == 0)
	// 					{
	// 						if(board[j][i-2*SIZE][k] == 1)
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
	// 					// printf("yoyoyo %d %d %d\n",r,i,t);
	// 					repeat = 1;
	// 					updateboard(r,i,t,board);
	// 					board[r][i][0] = t;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	return board;
=======
int *** loneranger(int ***board)
{
	int k;
	int repeat = 1;
	while(repeat == 1)
	{
		repeat = 0;

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
						repeat = 1;
						updateboard(i,r,t,board);
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
						if(board[j][i][0] == 0)
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
						repeat = 1;
						updateboard(r,i,t,board);
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
							if((board[j][l][0] == 0))
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
						repeat = 1;
						updateboard(u,r,t,board);
						board[u][r][0] = t;
					}
				}
		}
	}

	return board;


>>>>>>> 35adb7ea7f794eeacbdb70d36a7e473ab69d545a
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
