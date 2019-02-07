//[y][x]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int **result;
int **matrix1;
int **matrix2;
int **transposition;

void fillMatrixes (int n) 
{
	srand(time(NULL));
	
	result = malloc(n * sizeof(int *)); 
   for (int i = 0; i < n; i++)  
        result[i] = malloc(n * sizeof(int)); 
	
	transposition = malloc(n * sizeof(int *)); 
   for (int i = 0; i < n; i++)  
        transposition[i] = malloc(n * sizeof(int)); 
        
	matrix1 = malloc(n * sizeof(int *)); 
   for (int i = 0; i < n; i++) 
        matrix1[i] = malloc(n * sizeof(int));
        
   matrix2 = malloc(n * sizeof(int *)); 
   for (int i = 0; i < n; i++)  
        matrix2[i] = malloc(n * sizeof(int)); 	
        
   for (int i = 0; i < n; i++) 
	   for (int j = 0; j < n; j++)
		  	matrix1[j][i] = rand()%10;
		   	
	for (int i = 0; i < n; i++) 
	   for (int j = 0; j < n; j++)
		  	matrix2[j][i] = rand()%10;	   	 	   	
}	

void printMatrix (char* name, int n, int ** matrix) 
{
	printf("%s",name);
	for( int i = 0; i < n; i++ )
	{
  		printf("\n");
  		for (int j = 0; j < n; j++)
		  	printf("%d ",matrix[j][i]);
 	}
 	printf("\n");
}

void multiplyNaive (int n) 
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				result[i][j] = result[i][j] + (matrix1[i][k] * matrix2[k][j]);
}

void multiplyTransposition (int n) 
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
				transposition[i][j] = matrix2[j][i];
				
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				result[i][j] = result[i][j] + (matrix1[i][k] * transposition[j][k]);			
}

// changed order of for's
// k index on the inner-most loop like in multiplyNaive causes a cache miss in matrix2 on every iteration
// with j as the inner-most index, result and matrix2 are taken continuously, wheareas matrix1 remains the same 
void multiplyCacheFriendly (int n) 	
{
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j++)			
				result[i][j] = result[i][j] + (matrix1[i][k] * matrix2[k][j]);
}
void clearResult(int n)
{
   for (int i = 0; i < n; i++) 
	   for (int j = 0; j < n; j++)
		  	result[j][i] = 0;
}
       
int main(int argc, char* argv[]) 
{
	int n;
	double time;
	struct timeval begin;
	struct timeval end;
	
	printf("Give n which will stand for height and width of matrixes\n");
	scanf("%d",&n);	
	
	if (n <= 0) 
	{
		printf("Invalid data\n");
		return 0;
	}
	
	fillMatrixes(n);
	
	gettimeofday(&begin, NULL);
	multiplyNaive(n);
	gettimeofday(&end, NULL);
	time = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;
	printf("Time of the naive method: %17f seconds \n",time);

	clearResult(n);
	
	gettimeofday(&begin, NULL);
	multiplyTransposition(n);
	gettimeofday(&end, NULL);
	time = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;
	printf("Time of the transposition method: %9f seconds \n",time);

	clearResult(n);
	
	gettimeofday(&begin, NULL);
	multiplyCacheFriendly(n);
	gettimeofday(&end, NULL);
	time = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;
	printf("Time of the cache friendly method: %f seconds \n",time);

	free(matrix1);
	free(matrix2);
	free(result);
	free(transposition);
	
	return 0;
}


