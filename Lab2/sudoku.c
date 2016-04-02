#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int ***GetPossibilityMatrix(int** board)
{
    int ***x = (int***) malloc(SIZE*sizeof(int**));
    int i,j,k,l;
    
    int smallsz;
    if (SIZE==9)
        smallsz=3;
    if (SIZE==4)
        smallsz=2;
    if (SIZE==16)
        smallsz=4;

    for (i=0;i<SIZE;i++)
    {
        x[i] = malloc((SIZE)*sizeof(int*));
        for (j=0;j<SIZE;j++)
        {
            x[i][j]=malloc((SIZE+1)*sizeof(int));
            x[i][j][0]=0;
            for (k=1; k<=SIZE; k++)
                x[i][j][k]=1;
        }
    }
    for (i=0; i<SIZE;i++)
    {
        for (j=0; j<SIZE;j++)
        {
            if (board[i][j]>0)
            {
                // int k,l;
                for (k=0; k<SIZE;k++)
                {
                    x[i][k][board[i][j]]=0;
                    x[k][j][board[i][j]]=0;
                }
                // TODO KG: Put in for size 4 and 16
                int bx =i/smallsz;
                int by= j/smallsz;
                int m,n;
                for (m=smallsz*bx;m<smallsz*(bx+1);m++)
                {
                    for (n=smallsz*by;n<smallsz*(1+by);n++)
                    {
                        x[m][n][board[i][j]]=0;
                    }
                }
                for (m=1;m<=SIZE;m++)
                {
                    x[i][j][m]=0;    
                }
                x[i][j][0]=1;
                x[i][j][board[i][j]]=1;
            }
        }
    }
    return x;
}

void ShowPossibilityMatrix(int*** poss)
{
     int i,j,k;
     for (i=0;i<SIZE;i++)
     {
         for (j=0; j<SIZE; j++)
         {
             printf("[");
             for (k=1; k<=SIZE;k++)
             {
                  if (poss[i][j][k])
                      printf("%d,",k);
             }
             printf("],");
         }
         printf("\n");
     }
}

int** DFSPart(int** board)
{
    return board;
}

int** solveSudoku(int** board)
{
    printf("Size: %d\n",SIZE);
    int*** Possibilities= GetPossibilityMatrix(board);
    ShowPossibilityMatrix(Possibilities);
    board = DFSPart(board);
    return board;
}
