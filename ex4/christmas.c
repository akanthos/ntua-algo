#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (x) < (y) ? (x) : (y) 
#define MAX(x,y) (x) > (y) ? (x) : (y) 

typedef struct {
	int begin, end, w;
} edge_t;

typedef struct n{
	int node, w;
	struct n *next;
} node_t;

typedef struct {
	int father, plithos, kolpo;
} union_t;

typedef struct k{
	int node, weight;
	struct k *next;
} stack_t;

long k,count,lSize;
long long tree_weight, minimum;
char *buffer;
char temp[12];
stack_t *my_stack1=NULL, *my_stack2=NULL;

int i, j, N, M, temp1, temp2, temp3, temp4;
union_t *A;
edge_t *edges;
int ANSWER, FINAL;

void InsertionSort(edge_t* array, unsigned size)
{
    unsigned i;
    for(i = 1; i < size; ++i)
    {
        edge_t val = array[i];
        unsigned j = i;
        while(j > 0 && val.w < array[j-1].w)
        {
            array[j] = array[j-1];
            --j;
        }
        array[j] = val;
    }
}

unsigned Partition(edge_t * array, unsigned f, unsigned l,int pivot)
{
    unsigned i = f-1, j = l+1;
    while(1)
    {
        while(pivot < array[--j].w);
        while(array[++i].w < pivot);
        if(i<j)
        {
            edge_t tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
        else
            return j;
    }
}

void MedianHybridQuickSortImpl(edge_t *array, unsigned f, unsigned l)
{
    while(f+16 < l)
    {
        int v1 = array[f].w, v2 = array[l].w, v3 = array[(f+l)/2].w;
        int median =
            v1 < v2 ?
            ( v3 < v1 ? v1 : min(v2, v3)
             ) :
            ( v3 < v2 ? v2 : min(v1, v3)
             );
        unsigned m = Partition(array, f, l, median);
        MedianHybridQuickSortImpl(array, f, m);
        f = m+1;
    }
}

void MedianHybridQuickSort(edge_t *array, unsigned size)
{
    MedianHybridQuickSortImpl(array, 0, size-1);
    InsertionSort(array, size);
}

void unionTree(int x, int y, int w) {
	if (x == y) return;
	if (A[x].plithos > A[y].plithos)
	{
		A[y].father = x;
		A[y].kolpo = w;
		return;
	}
	if (A[x].plithos < A[y].plithos)
	{
		A[x].father = y;
		A[x].kolpo = w;
	}
	else
	{
		A[y].father = x;
		A[y].kolpo = w;
		A[x].plithos ++;
	}
}

int findTreePathCompression(int x) {
	while (x != A[x].father)
		x = A[x].father;
	return(x); 
}

int getnextnumber()
{
   while (buffer[k] < '0' || buffer[k] > '9') { ++k; if (k == lSize) return 0; }
   count = k;
   while (buffer[k] >= '0' && buffer[k] <= '9') {
      temp[k-count] = buffer[k];
      ++k;
      if (k == lSize) break;
   }
   temp[k-count] = '\0';
   return atoi(temp);
}

void insert_to_stack(stack_t **s, int x, int y)
{
	stack_t *temp = (stack_t *) malloc(sizeof(stack_t));
	temp -> node = x;
	temp -> weight = y;
	temp -> next = *s;
	*s = temp;
}

void remove_from_stack(stack_t **s, int *x, int *y)
{
	stack_t *temp = *s;
	*s = (*s)->next;
	*x = temp->node;
	*y = temp->weight;
	free(temp);
}

int main(int argc, char **argv)
{
	k=0;
	// obtain file size:
	fseek (stdin , 0 , SEEK_END);
	lSize = ftell (stdin);
	rewind (stdin);
	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	// copy the file insto the buffer:
	fread (buffer,1,lSize,stdin);
	N = getnextnumber();
	M = getnextnumber();
	A = (union_t *) malloc(N*sizeof(union_t));
	edges = (edge_t *) malloc(M*sizeof(edge_t));

	for (i=0; i<N; i++) 
	{
		A[i].father = i;
		A[i].plithos = 1;
		A[i].kolpo = -1;
	}
	for (i=0; i<M; i++)
	{
		edges[i].begin = getnextnumber();
		edges[i].end = getnextnumber();
		edges[i].w = getnextnumber();
	}
	MedianHybridQuickSort(edges, M);
	tree_weight = 0;
	i=0; // It counts the edges so that the while-loop doesn't try more than m times to add an edge
	j=0; // It counts how many edges have been put to the MaxST
	while (i<M && j<N-1)
	{
		temp1 = findTreePathCompression(edges[i].begin-1);
		temp2 = findTreePathCompression(edges[i].end-1);
		if ( temp1 != temp2 )
		{
			unionTree(temp1, temp2, edges[i].w);
			tree_weight += edges[i].w;
			edges[i].w = -1;
		}
		i++;
	}
	// Counting second best minimum spaninng tree...
	ANSWER = -1;
	minimum = 1844674407370962341;
	for (i=0; i<M; i++)
		if (edges[i].w > 0)
		{
			temp1 = edges[i].begin-1;
			temp2 = edges[i].end-1;
			while (A[temp1].father != temp1) {
				insert_to_stack(&my_stack1, temp1, A[temp1].kolpo);
				temp1 = A[temp1].father;
			}
			insert_to_stack(&my_stack1, temp1, A[temp1].kolpo);
			while (A[temp2].father != temp2) {
				insert_to_stack(&my_stack2, temp2, A[temp2].kolpo);
				temp2 = A[temp2].father;
			}
			insert_to_stack(&my_stack2, temp2, A[temp2].kolpo);

			while (my_stack1 && my_stack2)
			{
				remove_from_stack(&my_stack1, &temp1, &temp3);
				remove_from_stack(&my_stack2, &temp2, &temp4);
				if (temp1 != temp2) break;
			}
			ANSWER = MAX(ANSWER, temp3);
			ANSWER = MAX(ANSWER, temp4);
			while(my_stack1)
			{
				remove_from_stack(&my_stack1, &temp1, &temp2);
				ANSWER = MAX(ANSWER, temp2);
			}
			while(my_stack2)
			{
				remove_from_stack(&my_stack2, &temp1, &temp2);
				ANSWER = MAX(ANSWER, temp2);
			}
			minimum = min(minimum, edges[i].w - ANSWER);
		}

	printf("%lld %lld\n", tree_weight, tree_weight + minimum);
	return 0;
}
