/*  Simple recursive algorithm to solve the graph connectivity problem.  */

#include <stdio.h>
#include <stdlib.h>

/* initial size of the matrix we'll use to store the graph connections*/
#define initial_size 20

void clear_matrix(int** M, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			M[i][j] = 0;
}

void print_matrix(int** M, int size)
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			printf("%d ", M[i][j]);
		printf("\n");
	}
	printf("\n");
}

int** alloc_matrix(int size)
{
	int** M = (int**)malloc(size * sizeof(int*));
	
	int i;
	for(i = 0; i < size; i++)
		M[i] = (int*)malloc(size * sizeof(int));

	int j;
	/* Clear the new matrix */
	for (i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			M[i][j] = 0;

	return M; 
}


int** realloc_matrix(int** M, int old_size, int new_size)
{

	int** new_M = (int**)realloc(M, new_size * sizeof(int*));

	int i;
	int j;

	for(i = 0; i < old_size; i++)
	{
	/* Reallocate existing lines */
		new_M[i] = (int*)realloc(new_M[i], new_size * sizeof(int));
		
		/* Clear the new part of the line */
		for(j = old_size; j < new_size; j++)
			new_M[i][j] = 0;
	}


	for(i = old_size; i < new_size; i++)
	/* Allocate new lines */
	{
		new_M[i] = (int*)malloc(new_size * sizeof(int));

		/* Clear the new line */
		for(j = 0; j < new_size; j++)
			new_M[i][j] = 0;
	}

	return new_M;
}


void store_pair(int a, int b, int** M, int size)
/* store the connection a <-> b,
   by putting 'b' in row 'a' and 'a' in row 'b' */
{
	int i = 0;
	while (M[a][i] != 0 && i < size)
		i++;
	
	M[a][i] = b;

	i = 0;
	while (M[b][i] != 0 && i < size)
		i++;

	M[b][i] = a;
}

int can_imply(int last_origin, int origin, int destination, int** M, int size)
/* Can we get from 'origin' to 'destination',
   knowing one shouldn't go back to 'last_origin'? */
{
	int i;
	for(i = 0; i < size &&  M[origin][i] != 0 ; i++)
	/* M[origin][i] is a graph connected to 'origin' */
	{
		if (M[origin][i] == destination)
		/* Arrived at destination */
		{
			printf("It's possible to deduce:");
			printf("%d->", M[origin][i]);
			return 1;
		}
		else if (M[origin][i] != last_origin)
		/* We're not at destination, but we can try to get
		   to it through this graph */
		{
			/* This graph will be our new 'origin' */
			if ( can_imply(origin, M[origin][i], destination, M, size) )
			{
				/* We can get to 'destination' through this graph.
				   Print its ID, as it is part of the path to destination. */
				printf("%d->", M[origin][i]);
				return 1;
			}
		}	
	}

	return 0;
}

int main()
{
	int size = initial_size;

	int** M = alloc_matrix(size);
	
	printf("Input pairs of connected graphs, ");
	printf("giving each one a positive ID:\n");
	printf("If A and B are connected, input 'A-B'\n\n");
	
	int a, b;
	for(;;)
	{
		scanf("%d-%d", &a, &b);
		/* Get a pair of graphs*/	

		if((a >= size) || (b >= size))
		/* If one of the IDs is greater than the size of the matrix,
		   reallocate it */
		{
			if(a > b)
			{
				M = realloc_matrix(M, size, a + 1);
				size = a + 1;
			}
			else
			{
				M = realloc_matrix(M, size, b + 1);
				size = b + 1;
			}
		}	
		
		if ( !can_imply(a, a, b, M, size) )
		/* If it isn't possible to imply that both are connected,
		   store the pair */
		{
			store_pair(a, b, M, size);
			printf("Stored a new pair\n");
		}

		else
		/* The rest of the path will be printed by store_pair() */
			printf("%d\n", a);
	}

	return 0;
}
