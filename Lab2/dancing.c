#include <stdio.h>
#include <stdlib.h>


struct Node
{
	struct Node* Left;
	struct Node* Right;
	struct Node* Up;
	struct Node* Down;
	struct Node* ColumnNode;
	int iscolumn; // 0 for Dancing node, 1 for column
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
	Node_t temp;
	temp->Left = temp;
	temp->Right= temp;
	temp->Up = temp;
	temp->Down = temp;
	temp->size=0;
	if (type==0)
	{
		// Normal dancing node
		temp->ColumnNode = ctemp;
		temp->iscolumn=0;
	}
	else if (type==1)
	{
		// Column Node
		temp->ColumnNode=temp;
		temp->iscolumn = 1;
		temp->descl = ident;
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
		for (j=x->Left; j!=i; j=j->Left)
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
		if (c->size<min)
		{
			min= c->size;
			ret= c;
		}
	}
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

void Search(int k)
{
	if(Header->Right==Header)
	{
		//Handle Solution
		printf("Solution moment\n");
	}
	else
	{
		Node_t c;
		c=selectComumnNodeHeuristic();
		Cover(c);

		Node_t r,j;
		for (r=c->Down; r!= c; r=r->Down)
		{
			// answer.add(r);
			Answers[prevfilled]=r;
			prevfilled+=1;
			for (j=r->Right; j!=r; j=j->Right)
			{
				Cover(j->ColumnNode);
			}

			Search(k+1);

			r= Answers[prevfilled-1];
			prevfilled-=1;
			// r= answer.remove(answer.size()-1);
			c=r->ColumnNode;

			for(j=r->Left;j!=r;j=j->Left)
			{
				Uncover(j->ColumnNode);
			}
		}
		Uncover(c);
	}
}



Node_t MakeBoard(int** grid, int COLS, int ROWS)
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
				Node_t newNode = Node(0,col,0);
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

int main(int argc, char const *argv[])
{
	/* code */
	Answers=malloc(1000*sizeof(Node_t));

	return 0;
}