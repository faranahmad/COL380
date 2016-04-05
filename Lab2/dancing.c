#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "preprocess.c"
#include "sudoku.h"

struct Node
{
	struct Node* Left;
	struct Node* Right;
	struct Node* Up;
	struct Node* Down;
	struct Node* ColumnNode;
	// int iscolumn; // 0 for Dancing node, 1 for column
	int descl; // description for column node
	int size;
};

typedef struct Node* Node_t;

Node_t Header;
Node_t* Answers;
int prevfilled=0;

Node_t hookDown(Node_t self,Node_t n1)
{
	n1->Down=self->Down;
	n1->Down->Up = n1;
	n1->Up = self;
	self->Down=n1;
	return n1;
}

Node_t hookRight(Node_t self,Node_t n1)
{
	n1->Right = self-> Right;
	n1->Right->Left = n1;
	n1->Left = self;
	self->Right = n1;
	return n1;
}

void UnlinkLR(Node_t self)
{
	self->Left->Right = self->Right;
	self->Right->Left = self->Left;
}

void RelinkLR(Node_t self)
{
	self->Left->Right = self;
	self->Right->Left = self;
}

void UnlinkUD(Node_t self)
{
	self->Up->Down = self->Down;
	self->Down->Up = self->Up;
}

void RelinkUD(Node_t self)
{
	self->Up->Down = self;
	self->Down->Up = self;
}

Node_t Node(int type,Node_t ctemp, int ident)
{
	Node_t temp = malloc(sizeof(struct Node));
	temp->Left = temp;
	temp->Right= temp;
	temp->Up = temp;
	temp->Down = temp;
	temp->size=0;
	temp->descl=ident;
	if (type==0)
	{
		// Normal dancing node
		temp->ColumnNode = ctemp;
		// temp->iscolumn=0;
	}
	else if (type==1)
	{
		// Column Node
		temp->ColumnNode=temp;
		// temp->iscolumn = 1;
		// temp->descl = ident;
		// temp->size = 0;
	}
	return temp;
}

void Cover(Node_t x)
{
	// For column node
	UnlinkLR(x);
	Node_t temp,temp1;
	for (temp = x->Down; temp!= x;temp = temp->Down)
	{
		for (temp1 = temp->Right; temp1!=temp;temp1 = temp1->Right)
		{
			UnlinkUD(temp1);
			temp1->ColumnNode->size--;
		}
	}
	Header->size--;
}

void Uncover(Node_t x)
{
	// For column Node
	Node_t i,j;
	for (i=x->Up; i!=x; i=i->Up)
	{
		for (j=i->Left; j!=i; j=j->Left)
		{
			j->ColumnNode->size++;
			RelinkUD(j);
		}
	}
	RelinkLR(x);
	Header->size++;
}

Node_t SelectColumnNodeNaive()
{
	return Header->Right;
}

Node_t selectComumnNodeHeuristic()
{
	int min=99999;
	Node_t ret,c;
	for (c= Header->Right; c!=Header; c= c->Right)
	{
		if (min==0)
		{
			return ret;
		}
		if (c->size<min)
		{
			min= c->size;
			ret= c;
		}
	}
	// printf("Min value found: %d\n", min);
	return ret;
}

Node_t selectColumnNodeRandom()
{
	Node_t ret,c;
	c= Header->Right;
	// TODO: Put in random
	return c;
}

Node_t selectColumnNodeNth(int n)
{
	int go = n % Header->size;
	Node_t ret;
	int i;
	for (i=0;i<go;i++)
	{
		ret= ret->Right;
	}
	return ret;
}

void PrintBoard()
{
	printf("Board Config column wise\n");
	Node_t temp;
	for (temp=Header->Right; temp!= Header; temp=temp->Right)
	{
		Node_t d;
		printf("%d ->>> ", temp->descl);
		for (d=temp->Down; d!= temp; d=d->Down)
		{
			printf("%d -->", d->descl);
			Node_t i;
			// for (i=d->Right;i !=d; i = i->Right)
			// {
			// 	printf("%d --->", i->ColumnNode->descl);
			// }
			// printf("\n");
		}
		printf("\n");
	}

	printf("Board Config Row wise\n");
	// Node_t temp;
	for (temp=Header->Right; temp!= Header; temp=temp->Right)
	{
		Node_t d;
		printf("%d ->>> ", temp->descl);
		for (d=temp->Down; d!= temp; d=d->Down)
		{
			printf("%d <-> " , d->descl);
			Node_t i;
			printf("%d --->", d->ColumnNode->descl);
			for (i=d->Right;i !=d; i = i->Right)
			{
				printf("%d --->", i->ColumnNode->descl);
			}
			printf("\n");
		}
		printf("\n");
	}

}


void ShowAnswers()
{
	int i;
	printf("Answers are of length %d \n",prevfilled);
	for (i=0; i<prevfilled;i++)
	{
		printf("%d -> ", Answers[i]->descl);
	}
	printf("\n");
}

int Search(int k)
{
	if(Header->Right==Header)
	{
		//Handle Solution
		// printf("Solution moment, should exit\n");
		// PrintBoard();
		// ShowAnswers();
		return 1;
		// printf("Still going on\n");
	}
	else
	{
		Node_t c;
		c=selectComumnNodeHeuristic();
		// c=selectColumnNodeRandom();
		// printf("Best column to cover: %d\n",c->descl);
		if (c->size==0)
		{
			// printf("Solution route terminated, time to backtrack\n");
			return -1;
		}
		// printf("Covering up %d\n" , c->descl);
		// printf("Init size %d\n", c->size);
		// return 1;
		Cover(c);
		// PrintBoard();
		// printf("Covered up %d\n" , c->descl);
		
		// return 1;

		Node_t r,j;
		for (r=c->Up; r!= c; r=r->Up)
		{
			// answer.add(r);
			// printf("Adding %d to answers at location %d \n", r->descl, prevfilled );
			Answers[prevfilled]=r;
			// return 0;
			prevfilled+=1;
			for (j=r->Right; j!=r; j=j->Right)
			{
				Cover(j->ColumnNode);
			}
			// printf("Covered everything up\n");
			// PrintBoard();
			// return 0;
			int x =Search(k+1);
			if (x==-1)
			{
				// printf("Recursive solution not found\n");
				r= Answers[prevfilled-1];
				// printf("Removing %d from answers\n", r->descl);
				prevfilled-=1;
				// r= answer.remove(answer.size()-1);
				c=r->ColumnNode;
				// return -89;

				for(j=r->Left;j!=r;j=j->Left)
				{
					// printf("Unconvering for %d\n",j->ColumnNode->descl);
					Uncover(j->ColumnNode);
				}
				// printf("Done uncovering\n");
				// PrintBoard();
				// ShowAnswers();
				// return 98;
			}
			else if (x==1)
			{
				return 1;
			}
			// return 1;
		}
		Uncover(c);
		// printf("Done with everything, something broke\n");
		return -1;
	}
}



Node_t MakeBoard(int** grid, int ROWS, int COLS)
{
	Node_t headerNode = Node(1,NULL,-1);
	Node_t columnNodes[COLS];
	int i,j;
	for (i=0;i<COLS;i++)
	{
		Node_t n = Node(1,NULL,i);
		columnNodes[i]=n;
		headerNode = hookRight(headerNode,n);
	}
	headerNode = headerNode->Right->ColumnNode;

	for (i=0; i<ROWS;i++)
	{
		Node_t prev = NULL;
		for (j=0; j<COLS;j++)
		{
			if (grid[i][j]==1)
			{
				Node_t col = columnNodes[j];
				Node_t newNode = Node(0,col,i);
				if (prev==NULL)
				{
					prev=newNode;
				}
				hookDown(col->Up,newNode);
				prev=hookRight(prev,newNode);
				col->size++;
			}
		}
	}
	headerNode->size=COLS;
	return headerNode;
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
                int bx =i/MINIGRIDSIZE;
                int by= j/MINIGRIDSIZE;
                int m,n;
                for (m=MINIGRIDSIZE*bx;m<MINIGRIDSIZE*(bx+1);m++)
                {
                    for (n=MINIGRIDSIZE*by;n<MINIGRIDSIZE*(1+by);n++)
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

Node_t MakeSudokuNode(int** Board)
{
	Node_t headerNode = Node(1,NULL,-1);
	int szsq = SIZE*SIZE;
	int COLS = 4*SIZE*SIZE;
	int ROWS = SIZE*SIZE*SIZE;
	Node_t columnNodes[COLS];
	int i,j,k;
	for (i=0;i<COLS;i++)
	{
		Node_t n = Node(1,NULL,i);
		columnNodes[i]=n;
		headerNode = hookRight(headerNode,n);
	}
	headerNode = headerNode->Right->ColumnNode;

	int num, posx,posy;
	Node_t prev = NULL;
	int temp12=0;
	for (i=0; i<ROWS;i++)
	{
		// num = i/sqsz
		// pos = (i%sqsz)/SIZE , i%SIZE

		num=i/szsq;
		j=(i%szsq)/SIZE;
		k=i%SIZE;


		if (Board[j][k]==0 || Board[j][k]==num+1)
		{	
			temp12++;
			// res[szsq*i + SIZE*j + k][0*szsq+ j*SIZE + k] =1;
			Node_t col = columnNodes[0*szsq+ j*SIZE + k];
			Node_t newNode = Node(0,col,i);
			prev= newNode;
			hookDown(col->Up,newNode);
			prev=hookRight(prev,newNode);
			col->size++;

			// res[szsq*i + SIZE*j + k][1*szsq+ i*SIZE + j] =1;
			col = columnNodes[1*szsq+ num*SIZE + j];
			newNode = Node(0,col,i);
			hookDown(col->Up,newNode);
			prev=hookRight(prev,newNode);
			col->size++;			

			// res[szsq*i + SIZE*j + k][2*szsq+ i*SIZE + k] =1;
			col = columnNodes[2*szsq+ num*SIZE + k];
			newNode = Node(0,col,i);
			// prev= newNode;
			hookDown(col->Up,newNode);
			prev=hookRight(prev,newNode);
			col->size++;
			
			// res[szsq*i + SIZE*j + k][3*szsq+ i*SIZE+ MINIGRIDSIZE*(j/MINIGRIDSIZE) + (k/MINIGRIDSIZE)] =1;
			col = columnNodes[3*szsq+ num*SIZE+ MINIGRIDSIZE*(j/MINIGRIDSIZE) + (k/MINIGRIDSIZE)];
			newNode = Node(0,col,i);
			// prev= newNode;
			hookDown(col->Up,newNode);
			prev=hookRight(prev,newNode);
			col->size++;
		}
	}
	headerNode->size=COLS;
	printf("Number of rows %d out of %d \n",temp12 , ROWS);
	return headerNode;
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

int CheckEqual(int** b1,int**b2)
{
	int i,j;
	for (i=0;i<SIZE;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			if (b1[i][j]!=b2[i][j])
				return 0;
		}
	}
	return 1;
}


int** solveSudoku(int** Board)
{
	double fstart= omp_get_wtime();
	int*** Possibilities= GetPossibilityMatrix(Board);
    // ShowPossibilityMatrix(Possibilities);
    ShowBoard(Board);
    printf("Giving it to Faran\n");
    int**Board1 = FaranPart(Possibilities);

    // printf("Faran completed %d, %d\n",Board,Board1);
    while (CheckEqual(Board1,Board)==0)
    {
    	printf("Faran again\n");
    	Board = Board1;
    	Board1 = FaranPart(GetPossibilityMatrix(Board1));
    }
    ShowBoard(Board);
    
	double strt = omp_get_wtime();

	// int columns = 4*SIZE*SIZE;
	// int rows = SIZE*SIZE*SIZE;
	int szsq = SIZE*SIZE;
	// int **res = malloc(sizeof(int*)*rows);
	// int i1,j1;
	// for (i1=0; i1<rows; i1++)
	// {
	// 	res[i1]= (int*) calloc(columns,sizeof(int));
	// 	// for (j1=0;j1<columns;j1++)
	// 	// {
	// 	// 	res[i1][j1]=0;
	// 	// }
	// }
	// // res[i][0-SIZE*SIZE] is for 1 number constraint
	// // res[i][SIZE*SIZE-2] is for row constraints
	// // res[i][2SIZE*SIZE -3 ] is for column constraints
	// // res[i][3-4] is for grid constraints
	// // res[0-size*size] is for 0 in positions
	// // res[1-2] is for 1 in positions
	// //.
	// //.
	// // res[size-1  - size] is for size in positions
	// #pragma omp parallel
	// {
	// 	printf("In parallel section %d\n",omp_get_thread_num());
	// 	int i;
	// 	for (i=0;i<SIZE;i++)
	// 	{
	// 		if (i/SIZE==omp_get_thread_num())
	// 		{
	// 			int j;
	// 			for (j=0; j<SIZE;j++)
	// 			{
	// 				int k;
	// 				for (k=0; k<SIZE; k++)
	// 				{
	// 					// Putting i in j,k on the board
	// 					// Row affected = szsq*i + SIZE*j + k
	// 					// Column affected = j*SIZE + k
	// 					// Column affected = szsq + i*SIZE + j
	// 					// Column affected = 2*szsq + i*SIZE + k
	// 					// Column affected = 3*szsq + i*SIZE + 3*(j/3) + k/3
	// 					if (Board[j][k]==0 || Board[j][k]==i+1)
	// 					{	
	// 						res[szsq*i + SIZE*j + k][0*szsq+ j*SIZE + k] =1;
	// 						res[szsq*i + SIZE*j + k][1*szsq+ i*SIZE + j] =1;
	// 						res[szsq*i + SIZE*j + k][2*szsq+ i*SIZE + k] =1;
	// 						res[szsq*i + SIZE*j + k][3*szsq+ i*SIZE+ MINIGRIDSIZE*(j/MINIGRIDSIZE) + (k/MINIGRIDSIZE)] =1;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	
	double f1 = omp_get_wtime();

	// Header= MakeBoard(res,rows,columns);
	Header =MakeSudokuNode(Board);

	printf("Sudoku node done\n");

	double f2 = omp_get_wtime();

	// PrintBoard();
	Answers=malloc(1000*sizeof(Node_t));

	int y= Search(0);

	double f3 = omp_get_wtime();

	if (y==1)
	{
		for (y=0;y<prevfilled;y++)
		{
			int num = Answers[y]->descl;
			int dig = 1+ (num/szsq);
			int row = (num%szsq)/SIZE;
			int col = (num%SIZE);
			// printf("row: %d, col %d , num %d\n", row,col,dig);
			Board[row][col]=dig;
		}
	}
	printf( " Faran Time: %e \n",strt-fstart );
	printf( " Inititime: %e \n",f1-strt );
	printf( " Making Board Time: %e \n",f2-f1 );
	printf( " Solving Time: %e \n",f3-f2 );
	// printf( " Inititime: %if \n",f1-strt );

	return Board;	
}




// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	Answers=malloc(1000*sizeof(Node_t));

// 	int g1[6][7] = {
// 		{1,0,0,1,0,0,1},
// 		{1,0,0,1,0,0,0},
// 		{0,0,0,1,1,0,1},
// 		{0,0,1,0,1,1,0},
// 		{0,1,1,0,0,1,1},
// 		{0,1,0,0,0,0,1}
// 	};
	
// 	int g2[7][6] = {
// 		{1,1,0,0,0,0},
// 		{0,0,0,0,1,1},
// 		{0,0,0,1,1,0},
// 		{1,1,1,0,0,0},
// 		{0,0,1,1,0,0},
// 		{0,0,0,1,1,0},
// 		{1,0,1,0,1,1}
// 	};

// 	// int **x;
// 	// x = (int**) g1;
// 	Header = MakeBoard(g1,6,7);
// 	PrintBoard(Header);
// 	int y=Search(0);
// 	// printf("Returned\n");
// 	// PrintBoard(Header);
// 	return 0;
// }