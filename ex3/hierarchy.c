#include <stdio.h>
#include <stdlib.h>
struct Node
{
	unsigned short v;
	struct Node *next;
};
typedef struct Node NodeType;

char *gender, *m;
int Res[2]; /* Res[0]:rm, Res[1]:rf */
NodeType **G = NULL;
unsigned short *p, N, father;

void insert(unsigned short i)
{
	NodeType * temp = G[father];
	G[father] = (NodeType *) malloc(sizeof(NodeType));
	G[father]->v = i;
	G[father]->next = temp;
}

void DFS(unsigned short i, int *Sexes)
{
	NodeType *t=G[i];
	unsigned short neighbour;
	int NewSexes[2]; /* These are the Men and Women of all subtrees */
	// TODO: Initializations for Sexes
	if (i) 
		if (gender[i]=='m') 
		{	Sexes[0]=1;Sexes[1]=0;}
		else
		{	Sexes[0]=0;Sexes[1]=1;}
	else
	{Sexes[0]=Sexes[1]=0;}
//	printf("Node %hu --> Sexes[0]=%d Sexes[1]=%d\n", i, Sexes[0], Sexes[1]);
	// TODO: Make Node "Under Examination"
	m[i] = 'Y';
//	if (i) printf("Exploring node %hu...\n", i);
	// TODO: Examinate all children of Node
	while(t)
	{
		neighbour = t->v;
		if (m[neighbour]=='A') DFS(neighbour, NewSexes);
		Sexes[0] += NewSexes[0];
		Sexes[1] += NewSexes[1];
		t=t->next;
	}
	// TODO: Node Processing With Results From Children 
	if (i && gender[i]=='m') Res[0]+=Sexes[1];
	else if (i) Res[1]+=Sexes[0];
//	printf("Node %hu --> Res[0]=%d Res[1]=%d\n", i, Res[0], Res[1]);
	m[i] = 'E';
}
void DFS_init()
{
	unsigned short i;
	int Sexes[2]; /* Sexes[0]:Men, Sexes[1]:Women */
	m = (char *) malloc((N+1)*sizeof(char));
	Res[0]=Res[1]=0;
	for (i=0; i<=N; i++)
		m[i] = 'A';
	for (i=0; i<N; i++)
		if (m[i]=='A')
			DFS(i, Sexes);
	free(m);
}

void show_tree_list()
{
	NodeType *t = NULL;
	unsigned short i;
	for (i=0;i<=N;i++)
	{
		printf("Node %hu: ", i);
		t=G[i];
		while(t)
		{
			printf("%hu ", t->v);
			t=t->next;
		}
		printf("\n");
	}
}

int main(int argc, char ** argv)
{
	unsigned short i;
	scanf("%hu", &N);
	gender = (char *) malloc((N+1)*sizeof(char));
	p = (unsigned short *) malloc((N+1)*sizeof(unsigned short));
	G = (NodeType **) malloc((N+1)*sizeof(NodeType *));
	for (i=0 ; i<=N ; i++)
	{
		G[i]=NULL;
	}
	for (i=1 ; i<=N ; i++)
	{
		scanf("%hu %c", &father, gender+i);
		p[i] = father;
		insert(i);
	}
	DFS_init();
//	show_tree_list();
//	printf("%d\n", Res[0]);
//	printf("%d\n", Res[1]);
	printf("%d\n", Res[0]-Res[1]);
	free(G);
	free(p);
	free(gender);
	return 0;
}
