#include <stdio.h>
#include <stdlib.h>

int  check  (int, int, int, int , int *);
int decide (int, int, int, int *);

int main ()
{
	int i, N, K, *A;
	int max, output;
	scanf("%d %d", &N, &K);
	A = (int *) malloc (N*sizeof(int));

	max=0;
	for (i=0;i<N;i++)
	{
		scanf("%d", A+i);
		max += A[i];
	}

	if (K == 1)
	{
		printf("%d\n", max);
		free(A);
		return 0;
	}
	
	output = check(max/K, max, N, K, A);
	printf("%d\n", output);
	
	free(A);
	return 0;
}

int check (int low, int high, int N, int K, int *a)
{
	int med, output;
	if (high == low)
		return low;
	else
	{
		med = (low+high)/2;
		output = decide(med, N, K, a);
		if (output!=0)
			return check(low, med, N, K, a);
		else
			return check(med+1, high, N, K, a);
	}
}

int decide (int boundary, int N, int K, int *a)
{
	int i, k;
	int sum, max;
	for (max=0,sum=0,i=0,k=0;;)
	{
		if (i==N)
		{
			if (sum <= boundary)
			{
				if (max < sum) max = sum;
				return max;
			}
			else
			{
				i--;
				sum -= a[i];
				if (max < sum) max = sum;
				if (a[i] <= boundary)
				{
					if (k==K-1) return 0;
					if (max < a[i]) max = a[i];
					return max;
				}
				else 
					return 0;
			}
		}
		if (k==K)
		{
			if (sum > boundary)
			{
				sum -= a[--i];
				i++;
			}
			break;
		}
		if (sum <= boundary) sum += a[i++];
		else
		{
			sum -= a[--i];
			if (max < sum) max = sum; 
			sum = 0;
			k++;
		}
	}
}
