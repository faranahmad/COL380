/*2013CS10231_2013CS10220*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// #include "preprocess.c"
#include "sudoku.h"







int GlobalSolved;






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
	omp_set_num_threads(1);
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
					int t=0;
					int p = -1;
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
	int repeat = 1;
	omp_set_num_threads(1);
	while(repeat == 1)
	{
		repeat = 0;
		int i;
		#pragma omp parallel for
		for(i = 0;i < 3*SIZE;i++)
		{
			if(i < SIZE)
			{
				int k;
				// for(j = (i/GRIDSIZE)*GRIDSIZE;j < (i/GRIDSIZE+1)*GRIDSIZE;j++)
				// {
				// 	for(l = (i%GRIDSIZE)*GRIDSIZE;l < (i%GRIDSIZE + 1)*GRIDSIZE;l++)
				// 	{
						for(k = 1;k <= 10;k++)
						{
							int t,u,r,j1,l1;
							int count = 0;
							for(j1 = (i/GRIDSIZE)*(GRIDSIZE) ; j1 < (i/GRIDSIZE + 1)*(GRIDSIZE) ; j1++)
							{	
								for(l1 = (i%GRIDSIZE)*(GRIDSIZE) ; l1 < (i%GRIDSIZE + 1)*(GRIDSIZE) ; l1++)
								{
									if((board[j1][l1][0] == 0))
									{
										if(board[j1][l1][k] == 1)
										{
											t = k;
											u = j1;
											r = l1;
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
					// 	}
					// }
				}
				// printf("yahan pe done till here \n");
			}
			else if(i < 2*SIZE)
			{
				int k;
				for(k = 1;k <=10;k++)
				{
					int count = 0;
					int t = 0;
					int p = -1;
					int r;
					int j;
					for(j = 0; j < SIZE ; j++)
					{
						if(board[i-SIZE][j][0] == 0)
						{
							if(board[i-SIZE][j][k] == 1)
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
						updateboard(i-SIZE,r,t,board);
						board[i-SIZE][r][0] = t;
					}
				}
				// printf("yahan pe done till here 2 \n");	
			}
			else
			{
				// printf("reached here \n");	
				int k;
				for(k = 1;k <= 10 ;k++)
				{
					int count = 0;
					int t;
					int p = -1;
					int r;
					int j;
					for(j = 0; j < SIZE ; j++)
					{
						// printf("values %d %d %d \n",i-2*SIZE,j,k);
						if(board[j][i-2*SIZE][0] == 0)
						{
							if(board[j][i-2*SIZE][k] == 1)
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
						updateboard(r,i-2*SIZE,t,board);
						board[r][i-2*SIZE][0] = t;
					}
				}
				// printf("yahan pe done till here 3 \n");
			}

		}
	}
	return board;
}
// int *** loneranger(int ***board)
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























extern int thread_count;

int solved;

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
Node_t HeaderRev;
Node_t* Answers;
Node_t* AnswersRev;
int prevfilled=0;
int prevfilledRev=0;
Node_t* Final;
int finalans=0;


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

void CoverRev(Node_t x)
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
	HeaderRev->size--;
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

void UncoverRev(Node_t x)
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
	HeaderRev->size++;
}

Node_t SelectColumnNodeNaive()
{
	return Header->Right;
}

Node_t SelectColumnNodeNaiveRev()
{
	return HeaderRev->Right;
}


Node_t selectComumnNodeHeuristic()
{
	int min=99999;
	Node_t ret=NULL;
	Node_t c;
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

Node_t selectComumnNodeHeuristicRev()
{
	int min=99999;
	Node_t ret,c;
	for (c= HeaderRev->Right; c!=HeaderRev; c= c->Right)
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

// Node_t selectColumnNodeRandom()
// {
// 	Node_t c;
// 	c= Header->Right;
// 	// TODO: Put in random
// 	return c;
// }

// Node_t selectColumnNodeRandomRev()
// {
// 	Node_t c;
// 	c= HeaderRev->Right;
// 	// TODO: Put in random
// 	return c;
// }

// Node_t selectColumnNodeNth(int n)
// {
// 	int go = n % Header->size;
// 	Node_t ret;
// 	int i;
// 	for (i=0;i<go;i++)
// 	{
// 		ret= ret->Right;
// 	}
// 	return ret;
// }

// Node_t selectColumnNodeNthRev(int n)
// {
// 	int go = n % HeaderRev->size;
// 	Node_t ret;
// 	int i;
// 	for (i=0;i<go;i++)
// 	{
// 		ret= ret->Right;
// 	}
// 	return ret;
// }

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
			// Node_t i;
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
	if (GlobalSolved)
	{
		return -3;
	}
	if (solved!=0)
	{
		return -2;
	}
	if(Header->Right==Header)
	{
		//Handle Solution
		// printf("Solution moment, should exit\n");
		// PrintBoard();
		// ShowAnswers();
		solved=1;
		GlobalSolved=1;
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
			else
			{
				return x;
			}
			// else if(x==-2)
			// {
			// 	return -2;
			// }
			// else if (x==1)
			// {
			// 	return 1;
			// }
			// return 1;
		}
		Uncover(c);
		// printf("Done with everything, something broke\n");
		return -1;
	}
}


int SearchRev(int k)
{
	if (GlobalSolved)
	{
		return -3;
	}
	if(solved!=0)
	{
		return -2;
	}
	if(HeaderRev->Right==HeaderRev)
	{
		solved=1;
		GlobalSolved=1;
		return 1;
	}
	else
	{
		Node_t c;
		c=selectComumnNodeHeuristicRev();
		if (c->size==0)
		{
			return -1;
		}
		CoverRev(c);

		Node_t r,j;
		for (r=c->Down; r!= c; r=r->Down)
		{
			// answer.add(r);
			// printf("Adding %d to answers at location %d \n", r->descl, prevfilled );
			AnswersRev[prevfilledRev]=r;
			// return 0;
			prevfilledRev+=1;
			for (j=r->Right; j!=r; j=j->Right)
			{
				CoverRev(j->ColumnNode);
			}
			int x =SearchRev(k+1);
			if (x==-1)
			{
				r= AnswersRev[prevfilledRev-1];
				prevfilledRev-=1;
				c=r->ColumnNode;

				for(j=r->Left;j!=r;j=j->Left)
				{
					UncoverRev(j->ColumnNode);
				}
			}
			else
			{
				return x;
			}
		}
		UncoverRev(c);
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
    int i,j,k;
    
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

	int num;
	Node_t prev = NULL;
	// int temp12=0;
	for (i=0; i<ROWS;i++)
	{
		// num = i/sqsz
		// pos = (i%sqsz)/SIZE , i%SIZE

		num=i/szsq;
		j=(i%szsq)/SIZE;
		k=i%SIZE;


		if (Board[j][k]==0 || Board[j][k]==num+1)
		{	
			// temp12++;
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
	// printf("Number of rows %d out of %d \n",temp12 , ROWS);
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
	long long quotient;

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
        	int i,j;
        	for (i=0; i<SIZE;i++)
        	{
        		for (j=0;j<SIZE;j++)
        		{
        			StackBoards[presentnumber]->board[i][j]=0;
        		}
        		StackBoards[presentnumber]->rows[i]=0;
        		StackBoards[presentnumber]->columns[i]=0;
        		StackBoards[presentnumber]->grids[i]=0;

        	}
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
	// memcpy(destboard,srcboard,sizeof(Board));
    int i,j;
    destboard->remaining=srcboard->remaining;
    for (i=0; i<SIZE;i++)
    {
        for (j=0; j<SIZE; j++)
        {
            destboard->board[i][j]=srcboard->board[i][j];
        }
        destboard->rows[i]=srcboard->rows[i];
        destboard->columns[i]=srcboard->columns[i];
        destboard->grids[i]=srcboard->grids[i];
    }
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
	long long limt = 1;
	limt = limt << SIZE;
	if (num>SIZE || num==0)
	{
		printf("Trying to insert something huge and bad %d\n", num);
	}
	long long temp = m << (num-1);
	if (__builtin_ffsll(temp)>SIZE)
	{
		printf("Something bad is happening in temp part\n");
	}
	b->rows[x] |= temp;
	b->columns[y] |= temp;
	b->grids[(x/MINIGRIDSIZE)*MINIGRIDSIZE + y/MINIGRIDSIZE] |= temp;
	if (__builtin_popcountll(b->rows[x]) >SIZE)
	{
		printf("Something bad happened in row part\n");
	}	
	if (__builtin_popcountll(b->columns[y]) >SIZE)
	{
		printf("Something bad happened in row part\n");
	}	
	if (__builtin_popcountll(b->grids[(x/MINIGRIDSIZE)*MINIGRIDSIZE + y/MINIGRIDSIZE]) >SIZE)
	{
		printf("Something bad happened in row part\n");
	}
	if (b->rows[x]>limt)
		printf("Something bad in row value\n");
	if (b->columns[y]>limt)
		printf("Something bad in row value\n");
	if (b->grids[(x/MINIGRIDSIZE)*MINIGRIDSIZE + y/MINIGRIDSIZE]>limt)
		printf("Something bad in row value\n");

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


int CheckValid(Board_t x)
{
	int i,j;
	for (i=0;i<SIZE;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			long long pos1 = GetPossibilities(x,i,j);
			if (__builtin_popcountll(pos1) > SIZE)
			{
				return 0;
			}
		}
	}
	long long pos1 = GetPossibilities(x,0,6);
	printf("Value of pop count at 0, 6 %d\n",__builtin_popcountll(pos1));
	return 1;
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
		printf("Len of stack %d\n", pres);
		if (pres==0)
		{
			printf("Stack is empty\n");
			return inp;
		}

		pres-=1;
		temp = dfsstack[pres];
		if (CheckValid(temp)==0)
		{
			printf("INVLAID\n");
			exit(1);
		}
		m=Simplify(temp);
		if (CheckValid(temp)==0)
		{
			printf("INVLAID SIMPLIFY\n");
			exit(1);
		}
		printf("Simplified board %d\n",m);
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
							if (k<0)
							{
								if (CheckValid(temp)==0)
								{
									printf("INVALID\n");
									exit(1);
								}
								printf("%d,%d %lld\n",i,j,l);
								printf("pop count %d\n",__builtin_popcountll(l));
								int_to_bin(l);
								ShowBoard1(temp);
								exit(0);
							}
							printf("pop count %d\n",__builtin_popcountll(l));
							min=k;
							mini=i;
							minj=j;
							possib=l;
						}
					}
				}
			}
			printf("Min value obtained %d\n",min);
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
		// DeallocBoard(temp);
	}
	return inp;
}


int DFSPartThread(Board_t inp,Board_t ans)
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
		printf("Len of stack %d\n",pres);
		if (GlobalSolved==1)
		{
			return -2;
		}
		if (pres==0)
		{
			printf("Stack is empty\n");
			GlobalSolved = 1;
			return -1;
		}
		pres-=1;
		temp = dfsstack[pres];
		m=Simplify(temp);
		printf("Simplified board %d\n",m);
		// ShowBoard(temp);
		if (CheckFinished(temp))
		{
			printf("Found a solution!\n");
			GlobalSolved=1;
			// ShowBoard1(temp);
			// ans=temp;
			CopyBoard(temp,ans);
			return 1;
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
	return -1;
}





int** solveSudoku9(int ** board)
{
	// long long temp1=2;
	capacity = (SIZE+1)*(SIZE+1)*(SIZE+1);
	
	StackBoards = malloc(capacity*sizeof(Board_t));

	int i,j;
	for (i=0;i<capacity;i++)
	{
		StackBoards[i]=NULL;
		// StackBoards[i]=AllocBoard(1);
	}

	// printf("%d\n", __builtin_ffsll(temp1));
	// return board;
	// printf("Starting\n");
	Board_t y = GenerateBoard(board);
	if (CheckValid(y)==0)
	{	
		printf("GENERATED INCORRECT\n");
		exit(1);
	}
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

int** solveSudoku9Thread(int** board)
{
	capacity = (SIZE+1)*(SIZE+1)*(SIZE+1);
	
	StackBoards = malloc(capacity*sizeof(Board_t));

	int i,j;
	for (i=0;i<capacity;i++)
	{
		StackBoards[i]=NULL;
	}

	Board_t y = GenerateBoard(board);
	Board_t k = AllocBoard(0);
	int temp=DFSPartThread(y,k);
	// printf("Value of temp received %d\n",temp);
	// ShowBoard1(k);
	
	if (temp<0)
	{
		return NULL;
	}

	for (i=0;i<SIZE;i++)
	{
		for (j=0; j<SIZE;j++)
		{
			board[i][j]=k->board[i][j];
		}
	}
	// return 1;
	return board;
}






int **solveDLX(int** Board)
{
	solved=0;


	int szsq = SIZE*SIZE;
	// double fstart= omp_get_wtime();
	// int*** Possibilities= GetPossibilityMatrix(Board);
    // ShowPossibilityMatrix(Possibilities);
    // ShowBoard(Board);
    // printf("Giving it to Faran\n");
    // printf("Giving to faran\n");
    // int**Board1 = FaranPart(Possibilities);
    // Board=Board1;
    int **Board1=Board;
    // printf("Faran completed %d, %d\n",Board,Board1);
    // while (CheckEqual(Board1,Board)==0)
    // {
    // 	// printf("Faran again\n");
    // 	Board = Board1;
    // 	Board1 = FaranPart(GetPossibilityMatrix(Board1));
    // }
    // printf("Faran completed\n");
    // ShowBoard(Board);

	// double strt = omp_get_wtime();

	if (thread_count==1)
	{
		Header =MakeSudokuNode(Board);

		// double f2 = omp_get_wtime();

		// PrintBoard();
		Answers=malloc(szsq*sizeof(Node_t));
		// AnswersRev = malloc(1000*sizeof(Node_t));
		int y= Search(0);

		// double f3 = omp_get_wtime();

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
		// printf( " Faran Time: %e \n",strt-fstart );
		// printf( " Inititime: %e \n",f1-strt );
		// printf( " Making Board Time: %e \n",f2-strt );
		// printf( " Solving Time: %e \n",f3-f2 );
		// printf( " Inititime: %if \n",f1-strt );

		return Board;
	}
	else
	{
		// More than 1 thread available. We will use 2
		
		// double f2 = omp_get_wtime();

		// PrintBoard();


		omp_set_num_threads(2);
		#pragma omp parallel num_threads(2)
		{
			if (omp_get_thread_num()==1)
			{
				// Up solution
				Answers=malloc(szsq*sizeof(Node_t));
				Header =MakeSudokuNode(Board);
				int y= Search(0);
				// printf("Up returned %d\n", y);
				if (y==1)
				{
					// printf("Solved by Up\n");
					Final= Answers;
					finalans = prevfilled;
				}
				else if (y==-1)
				{
					solved=-1;
				}

			}
			else
			{
				// Down Solution
				AnswersRev = malloc(szsq*sizeof(Node_t));
				HeaderRev=MakeSudokuNode(Board1);
				int z=SearchRev(0);
				// printf("Down returned %d\n", z);
				if (z==1)
				{
					// printf("Solved by down\n");
					Final = AnswersRev;
					finalans = prevfilledRev;
				}
				else if(z==-1)
				{
					solved=-1;
				}
			}
			#pragma omp barrier
		}
		if (solved==1)
		{
			int y;
			for (y=0;y<finalans;y++)
			{
				int num = Final[y]->descl;
				int dig = 1+ (num/szsq);
				int row = (num%szsq)/SIZE;
				int col = (num%SIZE);
				// printf("row: %d, col %d , num %d\n", row,col,dig);
				Board[row][col]=dig;
			}			
		}
		// else if (solved==-1)
		// {

		// }
		// double f3 = omp_get_wtime();

		// printf( " Faran Time: %e \n",strt-fstart );
		// printf( " Inititime: %e \n",f1-strt );
		// printf( " Making Board Time: %e \n",f2-strt );
		// printf( " Solving Time: %e \n",f3-f2 );
		// printf( " Inititime: %if \n",f1-strt );

		return Board;
	}

}













int **GenerateGrid()
{
	int **temp123;
	temp123 = malloc(SIZE*sizeof(int*));
	int i;
	for (i=0;i<SIZE;i++)
	{
		temp123[i] = malloc(SIZE*sizeof(int));
	}
	return temp123;
}


int** solveSudoku(int** Board)
{
	int **temp = GenerateGrid();
	// for  
	int **temp1 = GenerateGrid();
	int solvedby;
	int  **temp2 = GenerateGrid();
	if (SIZE>=25)
	{
		if (thread_count==1)
		{
			return solveSudoku9(Board);
			// return solveDLX(Board);
		}
		else if (thread_count==2)
		{
			#pragma omp parallel num_threads(2)
			{
				if (omp_get_thread_num()==0)
				{
					// Solve stack
					temp = solveSudoku9Thread(Board);
					if (temp !=NULL)
					{
						solvedby=1;
						printf("Solved by stack\n");
					}
				}
				else
				{
					// Solve DLX
					solved=0;

					int szsq = SIZE*SIZE;

					Header =MakeSudokuNode(Board);

					Answers=malloc(szsq*sizeof(Node_t));

					int y= Search(0);

					if (y==1)
					{
						printf("Solved by DLX\n");
						solvedby=2;
						for (y=0;y<prevfilled;y++)
						{
							int num = Answers[y]->descl;
							int dig = 1+ (num/szsq);
							int row = (num%szsq)/SIZE;
							int col = (num%SIZE);
							temp1[row][col]=dig;
						}
					}
					// return Board;
				}
			}
			if (solvedby==1)
			{
				return temp;
			}
			else
			{
				return temp1;
			}		
		}
		else
		{
			#pragma omp parallel num_threads(3)
			{
				if (omp_get_thread_num()==0)
				{
					// Solve stack
					temp = solveSudoku9Thread(Board);
					if (temp !=NULL)
					{
						solvedby=1;
						printf("Solved by stack\n");
					}
				}
				else if (omp_get_thread_num()==1)
				{
					// Solve DLX
					solved=0;

					int szsq = SIZE*SIZE;

					Header =MakeSudokuNode(Board);

					Answers=malloc(szsq*sizeof(Node_t));

					int y= Search(0);

					if (y==1)
					{
						printf("Solved by DLX1\n");
						solvedby=2;
						for (y=0;y<prevfilled;y++)
						{
							int num = Answers[y]->descl;
							int dig = 1+ (num/szsq);
							int row = (num%szsq)/SIZE;
							int col = (num%SIZE);
							temp1[row][col]=dig;
						}
					}
					// return Board;
				}
				else if (omp_get_thread_num()==2)
				{
					// Solve DLX Reverse
					solved=0;

					int szsq = SIZE*SIZE;

					HeaderRev =MakeSudokuNode(Board);

					AnswersRev=malloc(szsq*sizeof(Node_t));

					int y= SearchRev(0);

					if (y==1)
					{
						printf("Solved by DLX2\n");
						solvedby=3;
						for (y=0;y<prevfilledRev;y++)
						{
							int num = AnswersRev[y]->descl;
							int dig = 1+ (num/szsq);
							int row = (num%szsq)/SIZE;
							int col = (num%SIZE);
							temp2[row][col]=dig;
						}
					}
					// return Board;
				}

			}
			if (solvedby==1)
			{
				return temp;
			}
			else if (solvedby==2)
			{
				return temp1;
			}
			else
			{
				return temp2;
			}		

		}
	}
	else
	{
		return solveSudoku9(Board);
	}

    	
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