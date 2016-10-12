#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (a>b)?a:b
typedef struct {
	int C, L, R;
} Game;
int pick_max(Game *Games, int *Score, int i, int lower_bound, int upper_bound)
{
	int k,max=0;
	if (lower_bound < 1) lower_bound = 1;
	for (k=lower_bound; k<=upper_bound; k++)
		if (Games[k].R+k < i) 
			if (max<Score[k]) max = Score[k];
	return max;
}
int main(int argc, char **argv)
{
	int N, Max=0, max, total_max=-1, i, *Score;
	Game *Games;
	/* Diavasma eisodou kai desmeusi xorou */
	scanf("%d",&N);
	Score = (int *) malloc((N+1)*sizeof(int));
	Games = (Game *) malloc((N+1)*sizeof(Game));
	scanf("%d",&(Games[1].C));
	scanf("%d",&(Games[1].L));
	scanf("%d",&(Games[1].R));
	total_max = Score[1] = Games[1].C;
	for (i=2; i<=N; i++)
	{
		scanf("%d",&(Games[i].C));
		scanf("%d",&(Games[i].L));
		scanf("%d",&(Games[i].R));
		Max = MAX(Max,Games[i-1].R);
		Max = MAX(Max,Games[i-1].L);
		max = pick_max(Games, Score, i, i-Games[i].L-1-Max, i-Games[i].L-1);
		Score[i] = Games[i].C+max;
		if (total_max<Score[i]) total_max=Score[i];
	}
	printf("%d\n", total_max);
	free(Score);
	free(Games);
	return 0;
}
