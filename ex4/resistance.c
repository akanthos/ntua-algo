#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (x) < (y) ? (x) : (y) 

typedef struct {
	int begin, end, w;
} edge_t;

long k,count,lSize;
char *buffer;
char temp[12];
int i, j, N, M, B, temp1, temp2;
int *A;
edge_t *edges;

static void InsertionSort(edge_t* array, unsigned size)
{
    unsigned i;
    for(i = 1; i < size; ++i)
    {
        edge_t val = array[i];
        unsigned j = i;
        while(j > 0 && val.w > array[j-1].w)
        {
            array[j] = array[j-1];
            --j;
        }
        array[j] = val;
    }
}

static unsigned Partition(edge_t * array, unsigned f, unsigned l,int pivot)
{
    unsigned i = f-1, j = l+1;
    while(1)
    {
        while(pivot > array[--j].w);
        while(array[++i].w > pivot);
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

static void MedianHybridQuickSortImpl(edge_t *array, unsigned f, unsigned l)
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

static void MedianHybridQuickSort(edge_t *array, unsigned size)
{
    MedianHybridQuickSortImpl(array, 0, size-1);
    InsertionSort(array, size);
}

static void unionTree(int x, int y) {
	if (x == y) return;
	A[y] = x;
//	A[x].size += A[y].size; 
}


static int findTreePathCompression(int x) {
	if (x != A[x])
		A[x] = findTreePathCompression(A[x]);
	return(A[x]);
}

static int getnextnumber()
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

int main(int argc, char **argv)
{
	k=0;
	// obtain file size:
	fseek (stdin , 0 , SEEK_END);
	lSize = ftell (stdin);
	rewind (stdin);
	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	// copy the file into the buffer:
	fread (buffer,1,lSize,stdin);
	N = getnextnumber();
	M = getnextnumber();
	B = getnextnumber();
	A = (int *) malloc(N*sizeof(int));
	edges = (edge_t *) malloc(M*sizeof(edge_t));
	for (i=0; i<N; i++) A[i] = i;
	for (i=0; i<M; i++)
	{	
		edges[i].begin = getnextnumber();
		edges[i].end = getnextnumber();
		edges[i].w = getnextnumber();
	}
	MedianHybridQuickSort(edges, M);
	i=0; // It counts the edges so that the while-loop doesn't try more than m times to add an edge
	j=0; // It counts how many edges have been put to the MaxST
	while (i<M && j<N-1)
	{
		temp1 = findTreePathCompression(edges[i].begin-1);
		temp2 = findTreePathCompression(edges[i].end-1);
		if ( temp1 != temp2 )
		{
			unionTree(temp1, temp2);
			edges[i].w = -1;
			j++;
		}
		i++;
	}
	i=M-1;
	j=0;
	while(i>=0 && B>=edges[i].w)
	{
		if (edges[i].w > 0)
		{
			B -= edges[i].w;
			j++;
		}
		i--;
	}
	printf("%d\n", j);
	return 0;
}
