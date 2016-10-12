#include <stdio.h>
#include <stdlib.h>
#define S(i,j) (Sums[j+1]-Sums[i])
#define max(a,b) (a>b)?a:b

int main (int argc, char **argv)
{
	int i, j, k, N, *Numbers=NULL, **A=NULL, *Sums=NULL;
	/* Diavasma eisodou kai deusmeusi mnimis */	
	scanf("%d",&N);
	Numbers = (int *) malloc(N * sizeof(int));
	Sums = (int *) malloc((N+1) * sizeof(int));
	Sums[0]=0;
	A = (int **) malloc(N * sizeof(int *));
	if(A == NULL)
	{
		printf("out of memory\n");
		exit(0);
	}
	for(i=0; i<N; i++)
	{
		A[i] = (int *) malloc(N * sizeof(int));
		if(A[i] == NULL)
		{
			printf("out of memory\n");
			exit(0);
		}
	}
	for (i=0;i<N;i++)
	{
		scanf("%d",Numbers+i);
		Sums[i+1]=Sums[i]+Numbers[i];
	}
	/* Ypologismos Apantisis */
	for (i=0;i<N;i++)
		A[i][i]=Numbers[i];
	for (k=1; k<N; k++)
		for (i=0,j=k; j<N; i++,j++)
			A[i][j] = max(Numbers[i]+(S(i+1,j)-A[i+1][j]), Numbers[j]+(S(i,j-1)-A[i][j-1]));
	/* Ektiposi Apotelesmatos */
	printf("%d %d\n", A[0][N-1], S(0,N-1)-A[0][N-1]);
	free(Sums);
	free(Numbers);
	free(A);
	return 0;
}
