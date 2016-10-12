#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BSIZE 1<<16
#define min(x,y) (x) < (y) ? (x) : (y) 
typedef struct graph{
	int node;
	int weight;
	struct graph *next;
} graph_node_t;

typedef struct heap{
	int node;
	long long priority;
	struct heap **p;
} heap_node_t;

char buffer[BSIZE];
int bpos = 0, bsize = 0;

int hs;
int N, M, *C=NULL;
long long weight, path;
long k,count,lSize;
char temp[12];
graph_node_t **G = NULL;
heap_node_t *Queue = NULL;
heap_node_t **Index=NULL;

void swap(heap_node_t *i, heap_node_t *j){
	heap_node_t temp;
	*(i->p) = j;
	*(j->p) = i;
	temp=*i; *i=*j; *j=temp;
	
}
int max(heap_node_t *A) { return(A[1].node); }
void combine(heap_node_t *A, int i) {
	int l, r, mp;
	l = 2*i; r = 2*i+1; mp = i;
	if ((l <= hs) && (A[l].priority < A[mp].priority))
		mp = l;
	if ((r <= hs) && (A[r].priority < A[mp].priority))
		mp = r;
	if (mp != i) 
	{
		swap(&A[i], &A[mp]);
		combine(A, mp);
	}
}
void combine_up(heap_node_t *A, int i) {
	int mp;
	mp = i/2;
	while ((mp>=1) && (A[i].priority < A[mp].priority))
	{
		swap(&A[i], &A[mp]);
		i = mp;
		mp = mp / 2;
	}
}

int deleteMax(heap_node_t *A) {
	int max;
//	if (isEmpty(A)) return(-1);
	max = A[1].node; *(A[1].p)=NULL;
	A[1] = A[hs];
	Index[A[hs].node] = &A[1];
	hs--;
	combine(A, 1);
	return(max);
}

void constructHeap(heap_node_t *A, int n) {
	int i;
	for (i = n / 2; i > 0; i--)
		combine(A, i);
}

void insert(int i, int j, int w)
{
	graph_node_t *temp = (graph_node_t *) malloc(sizeof(graph_node_t));
	temp->node = j;
	temp->weight = w;
	temp->next = G[i];
	G[i] = temp;
	temp = (graph_node_t *) malloc(sizeof(graph_node_t));
	temp->node = i;
	temp->weight = w;
	temp->next = G[j];
	G[j] = temp;
}


int readInt() 
{
	int d = 0, x = 0;
	char c;

	while(1) 
   	{
		if (bpos >= bsize) 
        	{
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}
int main()
{
	int i, n1, n2, w, odd1=0, odd2=0;
	graph_node_t *temp=NULL;
	N = readInt();
	M = readInt();
	C = (int *) malloc((N+1)*sizeof(int));
	G = (graph_node_t **) malloc((N+1)*sizeof(graph_node_t *));
	Queue = (heap_node_t *) malloc((N+1)*sizeof(heap_node_t));
	Index = (heap_node_t **) malloc((N+1)*sizeof(heap_node_t *));
	for (i=1; i<=N; i++)
	{
		C[i] = 0;
		G[i]=NULL;
		Queue[i].node = i;
		Queue[i].priority = INT_MAX;
		Queue[i].p = &Index[i];
		Index[i] = &Queue[i];
	}
	for (i=0; i<M; i++)
	{
		n1 = readInt(); C[n1]^=1;
		n2 = readInt(); C[n2]^=1;
		w = readInt(); weight += (long long) w;
		insert(n1, n2, w);
	}
	for (i=1; i<=N; i++)
	{
		if (C[i]) 
		{
			if (odd1==0) odd1=i;
			else odd2=i;
		}
	}
	Queue[odd1].priority = 0;
	hs = N;
	constructHeap(Queue, hs);
	w=0;
	while (w<N)
	{
		path = Queue[1].priority;
		n1 = deleteMax(Queue);
		w++;
		if (n1 == odd2) break;
		temp = G[n1];
		while(temp)
		{
			if (Index[temp->node]) 
			{
				if (Index[temp->node]->priority > path + ((long long) temp->weight))
				{
					Index[temp->node]->priority = path + ((long long) temp->weight);
					combine_up(Queue, Index[temp->node]-Queue);
				}
			}
			temp = temp->next;
		}
	}
	printf("%lld\n", path+weight);
	return 0;
}

