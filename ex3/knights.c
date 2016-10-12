#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	short x, y;
} Knight_t;

struct list_node
{
	short x, y, t;
	struct list_node *next;
};
typedef struct list_node List_Node_t;

short N, M, k, horse, time;
unsigned short min;
Knight_t **Maxes, *Knights, *temp_knight, next_positions[8];
short **Horse;
List_Node_t *List[2];

void enqueue(Knight_t *knight, short time)
{
	if (!List[0])
	{
		List[0] = (List_Node_t *) malloc(sizeof(List_Node_t));
		List[0]->x = knight->x;
		List[0]->y = knight->y;
		List[0]->t = time;
		List[0]->next = NULL;
		List[1] = List[0];
	}
	else
	{
		List_Node_t *temp = (List_Node_t *) malloc(sizeof(List_Node_t));
		temp->x = knight->x;
		temp->y = knight->y;
		temp->t = time;
		temp->next = NULL;
		List[1]->next = temp;
		List[1] = temp;
	}
}
void dequeue(short *time)
{
	if (List[0]) 
	{
		temp_knight->x = List[0]->x;
		temp_knight->y = List[0]->y;
		*time = List[0]->t;
		if (List[0] == List[1])
			List[0] = List[1] = NULL;
		else
			List[0] = List[0]->next;
	}
}

void find_next_positions()
{
	next_positions[0].x = temp_knight->x-1;	next_positions[0].y = temp_knight->y-2;
	next_positions[1].x = temp_knight->x-2;	next_positions[1].y = temp_knight->y-1;
	next_positions[2].x = temp_knight->x-2;	next_positions[2].y = temp_knight->y+1;
	next_positions[3].x = temp_knight->x-1;	next_positions[3].y = temp_knight->y+2;
	next_positions[4].x = temp_knight->x+1;	next_positions[4].y = temp_knight->y+2;
	next_positions[5].x = temp_knight->x+2;	next_positions[5].y = temp_knight->y+1;
	next_positions[6].x = temp_knight->x+2;	next_positions[6].y = temp_knight->y-1;
	next_positions[7].x = temp_knight->x+1;	next_positions[7].y = temp_knight->y-2;
}

short legal(short j)
{
	if (next_positions[j].x < 0 || next_positions[j].x >= N || next_positions[j].y < 0 || next_positions[j].y >= M) return 0;
	if (Horse[next_positions[j].x][next_positions[j].y] == horse) return 0;
	else 
	{
		Horse[next_positions[j].x][next_positions[j].y] = horse;
		return 1;
	}
}
void print_list()
{
	List_Node_t *t=List[0];
	while(t)
	{
		printf("Mpika ! ! !\n");
		printf("(%hi,%hi) ", t->x, t->y);
		t = t->next;
	}
	printf("\n");
}
void BFS()
{
	short j;
	while (List[0])
	{
		// TODO: Προσθήκη 100 πινάκων (3η διάσταση) 100x100 για να κρατούνται οι χρόνοι για κάθε άλογο... Ίσως 100 μεταβλητές min (μάλλον όχι)...
		dequeue(&time);
		if (Maxes[temp_knight->x][temp_knight->y].x < time) 
			Maxes[temp_knight->x][temp_knight->y].x = time;
		Maxes[temp_knight->x][temp_knight->y].y++;
//		printf("Exploring (%hi,%hi) derivatives...\n", temp_knight->x, temp_knight->y);
		find_next_positions();
		for (j=0; j<8; j++)
			if (legal(j))
				enqueue(next_positions+j, time+1);
	}
}

int main (int argc, char ** argv)
{
	short i, j;
	scanf("%hi %hi %hi", &N, &M, &k);
	Knights = (Knight_t *) malloc(k*sizeof(Knight_t));
	Maxes = (Knight_t **) malloc(N*sizeof(Knight_t *));
	Horse = (short **) malloc(N*sizeof(short *));
	temp_knight = (Knight_t *) malloc(sizeof(Knight_t));
	for (i=0; i<N; i++)
	{
		Maxes[i] = (Knight_t *) malloc(M*sizeof(Knight_t));
		Horse[i] = (short *) malloc(M*sizeof(short));
	}
	for (i=0; i<N; i++)
		for (j=0; j<M; j++)
		{
			Maxes[i][j].x = -1;
			Maxes[i][j].y = 0;
			Horse[i][j] = -1;
		}
	for (i=0; i<k; i++)
	{
		scanf("%hi %hi", &((Knights+i)->x), &((Knights+i)->y));
		(Knights+i)->x--;
		(Knights+i)->y--;
	}
	
	// TODO: BFS for every horse, fill in the Maxes array with max moves until ...
	min = 50000;
	for (horse=0; horse<k; horse++)
	{
		time = 0;
//		printf("\n\nChecking Horse %hi\n", horse);
		List[0] = List[1] = NULL;
		enqueue(Knights+horse, time);
		Horse[Knights[horse].x][Knights[horse].y] = horse;
		BFS(horse);
//		for (i=0; i<N; i++)
//		{
//			for (j=0; j<M; j++)
//			{
//				printf("%hi ", Maxes[i][j].x);
//			}
//			printf("\n");
//		}
//		printf("\n\n");
//		for (i=0; i<N; i++)
//		{
//			for (j=0; j<M; j++)
//			{
//				printf("%hi ", Maxes[i][j].y);
//			}
//			printf("\n");
//		}
	}
	for (i=0; i<N; i++)
		for (j=0; j<M; j++)
		{
			if (Maxes[i][j].y==k)
				if (min > Maxes[i][j].x) min = Maxes[i][j].x;
//			printf("Checking (%hi,%hi) : k=%hi x=%hi y=%hi ---> min = %hi\n", i, j, k, Maxes[i][j].x, Maxes[i][j].y, min);
		}
	
	if (min==50000) printf("-1\n");
	else printf("%hu\n", min);
	free(Maxes);
	free(Horse);
	free(Knights);
	return 0;
}
