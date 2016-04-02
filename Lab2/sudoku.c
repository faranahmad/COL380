#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int*** StackBoards;
int capacity;
int presentnumber;
int smallsz;


int CheckFinished(int** board)
{
    int i,j;
    for (i=0; i<SIZE; i++)
    {
        for (j=0;j<SIZE; j++)
        {
            if (board[i][j]==0)
                return 0;
        }
    }
    return 1;
}

int** AllocBoard(int type)
{
    if ((capacity>=presentnumber) && (type==0))
    {
        presentnumber+=1;
        return StackBoards[presentnumber-1];
    }
    else
    {
        printf("Allocating from stack\n");
        int ** y= malloc(SIZE*sizeof(int*));
        int k;
        for (k=0; k<SIZE;k++)
        {
            y[k]=malloc(SIZE*sizeof(int));
        }
        return y;
    }
}


void CopyBoard(int** srcboard,int** destboard)
{
    int i,j;
    for (i=0; i<SIZE;i++)
    {
        for (j=0; j<SIZE; j++)
        {
            destboard[i][j]=srcboard[i][j];
        }
    }
}

void DeallocBoard(int** board)
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


int ***GetPossibilityMatrix(int** board)
{
    int ***x = (int***) malloc(SIZE*sizeof(int**));
    int i,j,k,l;
    
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
                x[i][j][0]=board[i][j];
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

void GetPossiblePositions(int** board,int x, int y,int* poss)
{
    int i,j,k,l;
    for (i=0; i<=SIZE; i++)
    {
        poss[i]=1;
    }
    for (i=0; i<SIZE; i++)
    {
        if (board[x][i]!=0)
        {
            poss[board[x][i]]=0;
        }
        if (board[i][y]!=0)
        {
            poss[board[i][y]]=0;
        }
    }
    k=x/smallsz;
    l=y/smallsz;
    for (i=k*smallsz;i<smallsz*(1+k);i++)
    {
        for (j=l*smallsz;j<smallsz*(1+l);j++)
        {
            if (board[i][j]!=0)
                poss[board[i][j]]=0;
        }
    }    
}

void ShowBoard(int** x)
{
    int i,j;
    for (i=0; i<SIZE; i++)
    {
        for (j=0; j<SIZE; j++)
        {
            printf ("%d ", x[i][j]);
        }
        printf("\n");
    }
}

int** DFSPart(int** board)
{
    int n1 = capacity;
    int pres = 0;
    int *** dfsstack = malloc(n1*sizeof(int**));
    int** temp = AllocBoard(0);
    CopyBoard(board,temp);
    dfsstack[pres]=temp;
    pres = 1;
    int *PosibRow = malloc((1+SIZE)*sizeof(int));
    int i,j,k,l,found;
    while (1)
    {
        if (pres==0)
        {
            printf("Stack became empty\n");
        }
        pres -=1;
        temp = dfsstack[pres];
        // if (CheckFinished(temp))
        // {
        //     return temp;
        // }
        found=0;
        for (i=0; (i<SIZE) && (found==0);i++)
        {
            for (j=0;(j<SIZE) && (found==0);j++)
            {
                // ShowBoard(temp);
                // printf("i = %d , j =%d, pres = %d stackno=%d \n",i,j,pres,presentnumber);
                if (temp[i][j]==0)
                {
                    found=1;
                    GetPossiblePositions(temp,i,j,PosibRow);
                    for (k=1;k<=SIZE;k++)
                    {
                        if (PosibRow[k])
                        {
                            int **temp1 = AllocBoard(0);
                            CopyBoard(temp,temp1);
                            temp1[i][j]=k;
                            dfsstack[pres]=temp1;
                            pres+=1; 
                        }
                    }
                    DeallocBoard(temp);
                }
            }
        }
        if (found==0)
        {
            printf("Solution found\n");
            ShowBoard(temp);
            return temp;
        }
    }
    return board;
}

int** solveSudoku(int** board)
{

    if (SIZE==9)
        smallsz=3;
    if (SIZE==4)
        smallsz=2;
    if (SIZE==16)
        smallsz=4;

    // int *PosibRow = malloc((1+SIZE)*sizeof(int));
    // ShowBoard(board);
    // GetPossiblePositions(board, 0,8, PosibRow);
    // int i1=0;
    // for (;i1<=SIZE; i1++)
    // {
    //     if (PosibRow[i1])
    //         printf("%d ",i1);
    // }
    // printf("\n");

    // return board;


    capacity=(SIZE+1)*(SIZE+1)*(SIZE+1);
    presentnumber=0;
    StackBoards= malloc(capacity*sizeof(int**));
    int i;
    for (i=0; i<capacity;i++)
    {
        StackBoards[i]=AllocBoard(1);
    }
    printf("Size: %d\n",SIZE);
    int*** Possibilities= GetPossibilityMatrix(board);
    ShowPossibilityMatrix(Possibilities);
    board = DFSPart(board);
    return board;
}
