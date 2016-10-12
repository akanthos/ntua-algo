#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

void swap(short *, short*);
short readTable (short, short *);
void quickSort(short *, short, short);
short check(short *, short, short *);
short merge(short *left, short *right, short l_length, short r_length, short *);

int main (int argc, char **argv)
{
	short elements_read, T, N, *A, *B=NULL;
	
	// PARAXORISI MNIMIS GIA TON PINAKA
	A = (short *) malloc (MAX_SIZE*sizeof(short));

	// DIAVASMA TOY PLITHOUS TON GRAMMON 
	scanf("%hd", &T);

	// DIAVASMA TON GRAMMON KAI EPEXERGASIA TOUS 
	while (T-->0)
	{	// DIAVASMA THS KATHE GRAMMIS KAI EPEXERGASIA THS

		scanf("%hd", &N);
		elements_read=readTable(N, A);
				
		// ARXIKI TAXINOMISI TIS GRAMMIS 
		quickSort(A, 0, elements_read-1);
	
		// ELEGXOS AN IPARXEI XWROS GIA TIN MERGE STO TELOS TOU PINAKA POU EXO DESMEUSEI
		if (MAX_SIZE >= 2*elements_read) 
		{
			B = A+elements_read;
		}
		else
		{
			B = NULL;
		}

		// ELEGXOS ORTHOTITAS TIS GRAMMIS
		if (check(A, elements_read, B))
			printf("Possible\n");
		else
			printf("Not possible\n");
	}

	free(A);
	
	return 0;
}

short readTable (short N, short * A)
{
	short i=0;
	while (N-->0)
	{
		scanf("%hd", A+i);
		if (A[i]!=0) i++;
	}
	return i;
}

short check (short *a, short elem, short *b)
{
	short i=0, j;
	
	if (elem == 0) return 1;
	if (*a>elem-1) return 0;
	for (i=1;i<=*a;i++)
		(*(a+i))--;

	if (i == elem)
	{
		for (i=1,j=1;i<=*a;i++)
		{
			if (*(a+i)!=0) 
			{
				*(a+j)=*(a+i);
				j++;
			} 
		}
		return check(a+1, j-1, b);
	}
	else
	{
		i = merge(a+1, a+i, i-1, elem-i, b);
		return check(a+1, i, b);
	}
	
}

short merge(short *left, short *right, short l_length, short r_length, short *b)
{
	short *temp;
	if (b) temp = b;
	else temp = (short *) malloc ((l_length+r_length)*sizeof(short));
	short i=0,j=0,k=0;

	for (i=0,j=0,k=0 ; i<l_length && j<r_length ; )
	{
		if (*(left+i) == 0)
		{
			i++;
			continue;
		}
		if (*(right+j) == 0)
		{
			j++;
			continue;
		}
		if (*(left+i)>*(right+j))
		{
			temp[k] = *(left+i);
			i++;
			k++;
		}
		else
		{
			temp[k] = *(right+j);
			j++;
			k++;
		}
	}
	
	if (i == l_length)
	{
		for (;j<r_length;j++)
		{
			if (*(right+j)!=0)
			{
				temp[k]=*(right+j);
				k++;
			}
		}
	}
	else
	{
		for (;i<l_length;i++)
		{
			if (*(left+i)!=0)
			{
				temp[k]=*(left+i);
				k++;
			}
		}

	}
	for (i=0;i<k;i++)
	{
		*(left+i) = temp[i];
	}
	if (!b) free(temp);
	return k;
}

void swap (short *x, short *y)
{
  short t=*x; *x=*y; *y=t;
}

void quickSort (short *A, short left, short right)
{
	if (left>right) return;

	short pivot = A[(left+right)/2];

	short i=left, j=right;
	do
	{
		while (A[i]>pivot && i<=right) i++;
		while (A[j]<pivot && j>=left) j--;
		
		if (i<=j)
		{
			swap(&A[i],&A[j]);
			i++;j--;
		}

	} while (i<=j);
	
	quickSort(A, left, j);
	quickSort(A, i, right);
}

