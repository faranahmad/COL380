#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <omp.h>

extern int thread_count;

typedef struct 
{
	int board[SIZE][SIZE];
	int remaining;
	long long rows[SIZE];
	// Stores info if a row is occupied by a given number
	long long columns[SIZE];
	// Stores info if a column is occupied by a given number
	long long grids[SIZE];
	// Stores info if a grid is occupied by a given number
} Board;

typedef Board* Board_t;

Board_t* StackBoards;
int capacity;
int presentnumber;
int Counts[SIZE];
int Lasts[SIZE];

void int_to_bin(long long k)
{
	long long remainder,quotient;

    int binaryNumber[200],i=1,j;

    quotient = k;


    while(quotient!=0)
    {

         binaryNumber[i++]= quotient % 2;

         quotient = quotient / 2;

    }
    for(j = i -1 ;j> 0;j--)
         printf("%d",binaryNumber[j]);
    printf("\n");
}

Board_t AllocBoard(int type)
{
	if ((capacity>=presentnumber) && (type==0))
    {
    	if (StackBoards[presentnumber]!=NULL)
    	{
        	presentnumber+=1;
        	return StackBoards[presentnumber-1];
        }
        else
        {
        	StackBoards[presentnumber] = malloc(sizeof(Board));
        	presentnumber+=1;
        	return StackBoards[presentnumber-1];
        }
    }
    else
    {
        Board_t y= malloc(sizeof(Board));
        return y;
    }
}

void CopyBoard(Board_t srcboard,Board_t destboard)
{
	memcpy(destboard,srcboard,sizeof(Board));
    // int i,j;
    // for (i=0; i<SIZE;i++)
    // {
    //     for (j=0; j<SIZE; j++)
    //     {
    //         destboard[i][j]=srcboard[i][j];
    //     }
    // }
}

void DeallocBoard(Board_t board)
{
    if (presentnumber<capacity)
    {
        presentnumber-=1;
        StackBoards[presentnumber]=board;
    }
    else
    {
        printf("Dealloc failing stack\n");
    }
}

void InsertBoard(Board_t b, int num, int x, int y)
{
	if (b->board[x][y]>0)
	{
		printf("SOME BAD THING IS HAPPENING\n");
	}
	b->board[x][y]=num;
	b->remaining--;
	long long m =1;
	long long temp = m << (num-1);
	b->rows[x] |= temp;
	b->columns[y] |= temp;
	b->grids[(x/MINIGRIDSIZE)*MINIGRIDSIZE + y/MINIGRIDSIZE] |= temp;
}

void ShowBoard1(Board_t x)
{
	printf("Sudoku board contents: \n");
	int i,j;
	for (i=0; i<SIZE; i++)
	{
		for (j=0;j<SIZE; j++)
		{
			printf(" %d ,", x->board[i][j]);
		}
		printf("\n");
	}
	printf("Numbers left %d\n", x->remaining);
	printf("Row Possibilities \n");
	for (i=0; i<SIZE; i++)
	{
		printf("%d %lld\n",i,x->rows[i]);
	}
	printf("Column Possibilities \n");
	for (i=0; i<SIZE; i++)
	{
		printf("%d %lld\n",i,x->columns[i]);
	}
	printf("Grid Possibilities \n");
	for (i=0; i<SIZE; i++)
	{
		printf("%d %lld\n",i,x->grids[i]);
	}

}

Board_t GenerateBoard(int** x)
{
	Board_t y = malloc(sizeof(Board));
	y->remaining = SIZE*SIZE;
	int i,j;
	for (i=0;i<SIZE;i++)
	{
		y->rows[i]=0;
		y->columns[i]=0;
		y->grids[i]=0;
	}
	for (i=0;i<SIZE;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			if (x[i][j])
			{
				InsertBoard(y,x[i][j],i,j);
			}
		}
	}
	return y;
}

long long GetPossibilities(Board_t x,int i,int j)
{
	// ith row, jth column
	long long row = x->rows[i];
	long long col = x->columns[j];
	long long grid = x->grids[(i/MINIGRIDSIZE)*MINIGRIDSIZE + j/MINIGRIDSIZE];

	return (row|col|grid);
}

int CheckFinished(Board_t x)
{
	return (x->remaining==0);
}

int Elimination(Board_t x)
{
	int i,j;
	int done=0;
	for (i=0; i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if (x->board[i][j] ==0)
			{
				long long poss = (GetPossibilities(x,i,j));
				int numposs = __builtin_popcountll(poss);
				// printf("Numposs at %d, %d : %d\n", i,j, numposs );
				if (numposs==SIZE-1)
				{
					int val = __builtin_ffsll(~poss);
					// printf("Inserting %d at %d,%d\n", val,i,j );
					InsertBoard(x,val,i,j);
					done=1;
				}
				else if (numposs==SIZE)
				{
					return -100;
				}
			}
		}
	}
	return done;
}

int Loneranger(Board_t x)
{
	int i,j,k,l,done=0;
	long ident=1;


	for(j=0;j<SIZE;j++)
	{
		Counts[j]=0;
		Lasts[j]=0;
	}

	for (i=0;i<SIZE;i++)
	{
		// Row 
		for (j=0;j<SIZE;j++)
		{
			// Column
			if (x->board[i][j]==0)
			{
				long long poss = ~GetPossibilities(x,i,j);
				for (k=0;k<SIZE;k++)
				{
					// Number considered
					if ((poss) & (ident<<k)) 
					{
						Counts[k]+=1;
						Lasts[k]=j;
					}
				}
			}
		}
		for (j=0;j<SIZE;j++)
		{
			if (Counts[j]==1)
			{
				// printf("Trying to insert %d at %d,%d which has %d\n", j+1, i,Lasts[j],x->board[i][Lasts[j]]);
				if (x->board[i][Lasts[j]]==0)
				{
					InsertBoard(x,j+1,i,Lasts[j]);
					done=1;
				}
				else
				{
					return -100;
				}
			}
			Counts[j]=0;
			Lasts[j]=0;
		}
	}

	for (i=0;i<SIZE;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			if (x->board[j][i]==0)
			{
				long long poss = ~GetPossibilities(x,j,i);
				for (k=0;k<SIZE;k++)
				{
					if ((poss) & (ident<<k))
					{
						Counts[k]++;
						Lasts[k]=j;
					}
				}
			}
		}
		for (j=0;j<SIZE;j++)
		{
			if (Counts[j]==1)
			{
				if (x->board[Lasts[j]][i]==0)
				{
					InsertBoard(x,j+1,Lasts[j],i);
					done=1;
				}
				else
				{
					return -100;
				}
			}
			Counts[j]=0;
			Lasts[j]=0;
		}
	}

	for (i=0;i<SIZE;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			k=(i/MINIGRIDSIZE)*MINIGRIDSIZE + j/MINIGRIDSIZE;
			l=(i%MINIGRIDSIZE)*MINIGRIDSIZE + j%MINIGRIDSIZE;
			if (x->board[k][l]==0)
			{
				long long poss = ~GetPossibilities(x,k,l);
				for (k=0;k<SIZE;k++)
				{
					if ((poss) & (ident<<k))
					{
						Counts[k]++;
						Lasts[k]=j;
					}
				}
			}
		}
		for (j=0;j<SIZE;j++)
		{
			if (Counts[j]==1)
			{
				k=(i/MINIGRIDSIZE)*MINIGRIDSIZE + Lasts[j]/MINIGRIDSIZE;
				l=(i%MINIGRIDSIZE)*MINIGRIDSIZE + Lasts[j]%MINIGRIDSIZE;
			
				if (x->board[k][l]==0)
				{
					InsertBoard(x,j+1,k,l);
					done=1;
				}
				else
				{
					return -100;
				}
			}
			Counts[j]=0;
			Lasts[j]=0;
		}
	}

	return done;
}

int Simplify(Board_t x)
{
	int y= Elimination(x) + Loneranger(x);
	while (y>0)
	{
		y = (Elimination(x)) +Loneranger(x);
		// y +=  + loneranger(x));
	}
	return y;
}

Board_t DFSPart(Board_t inp)
{
	int n1= capacity;
	int pres=0;
	Board_t * dfsstack = malloc(n1*sizeof(Board_t));
	Board_t temp = AllocBoard(0);
	CopyBoard(inp,temp);
	dfsstack[pres]=temp;
	pres=1;
	int i,j,k,l,m;
	long long possib;
	while(1)
	{
		if (pres==0)
		{
			printf("Stack is empty\n");
			return inp;
		}
		pres-=1;
		temp = dfsstack[pres];
		m=Simplify(temp);
		// printf("Simplified board\n");
		// ShowBoard(temp);
		if (CheckFinished(temp))
		{
			printf("Found a solution!\n");
			// ShowBoard(temp);
			return temp;
		}
		if (m>=0)
		{
			int min, mini,minj;
			min =999999;
			for(i=0;i<SIZE;i++)
			{ 
				for(j=0;j<SIZE;j++)
				{
					if (temp->board[i][j]==0)
					{
						l = GetPossibilities(temp,i,j);
						k = SIZE - __builtin_popcountll(l);
						if (k && (k<min) )
						{
							min=k;
							mini=i;
							minj=j;
							possib=l;
						}
					}
				}
			}
			if  (min<999999)
			{ 
				// printf("Expanding position %d, %d with %d\n", mini,minj,min);
				// ShowBoard(temp);
				// int_to_bin(possib);
				// return temp;
				long ident=1;
				for (i=0;i<SIZE;i++)
				{
					if ((~possib) & (ident<<i))
					{
						// printf("Putting the value: %d\n",i+1);
						Board_t temp1 = AllocBoard(0);
						CopyBoard(temp,temp1);
						InsertBoard(temp1,i+1,mini,minj);
						dfsstack[pres]=temp1;
						pres+=1;
						// printf("Numbers in stack %d out of %d \n", pres, capacity);
					}
				}
			}
		}
		// return temp;
		DeallocBoard(temp);
	}
	return inp;
}

int** solveSudoku(int ** board)
{
	memset(Counts,0,SIZE*sizeof(int));
	memset(Lasts,0,SIZE*sizeof(int));

	long long temp1=2;
	capacity = (SIZE+1)*(SIZE+1)*(SIZE+1);
	
	StackBoards = malloc(capacity*sizeof(Board_t));

	int i,j;
	for (i=0;i<capacity;i++)
	{
		StackBoards[i]=NULL;
		// StackBoards[i]=AllocBoard(1);
	}

	printf("%d\n", __builtin_ffsll(temp1));
	// return board;
	// printf("Starting\n");
	Board_t y = GenerateBoard(board);
	// Simplify(y);
	// ShowBoard(y);
	// return board;
	// printf("Generated\n");
	// Simplify(y);
	y=DFSPart(y);
	// ShowBoard(y);

	for (i=0;i<SIZE;i++)
	{
		for (j=0; j<SIZE;j++)
		{
			board[i][j]=y->board[i][j];
		}
	}
	return board;
}