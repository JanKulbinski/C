//gcc -pthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **result;
int **matrix1;
int **matrix2;
int current_raw; 
int yMatrix1, xMatrix1, yMatrix2, xMatrix2, numberOfThreads; 
pthread_t *threads;
pthread_mutex_t lock;

void fillMatrixes() 
{
	srand(time(NULL));
	
	result = malloc(xMatrix2 * sizeof(int *)); 
   for( int i = 0; i < xMatrix2; i++ )  
        result[i] = malloc(yMatrix1 * sizeof(int)); 
	
	matrix1 = malloc(xMatrix1 * sizeof(int *)); 
   for( int i = 0; i < xMatrix1; i++ )  
        matrix1[i] = malloc(yMatrix1 * sizeof(int));
        
   matrix2 = malloc(xMatrix2 * sizeof(int *)); 
   for( int i = 0; i < xMatrix2; i++ )  
        matrix2[i] = malloc(yMatrix2 * sizeof(int)); 	
        
   for( int i = 0; i < yMatrix1; i++ ) 
	   for( int j = 0; j < xMatrix1; j++ )
		  	matrix1[j][i] = rand()%2;
		   	
	for( int i = 0; i < yMatrix2; i++ ) 
	   for( int j = 0; j < xMatrix2; j++ )
		  	matrix2[j][i] = rand()%2;	   	 	   	
}	

void *multiply( void *arg )  
{

	int x = xMatrix2; 		// resultMatrix x
	int y = yMatrix1;		// resultMatrix y
	
	int i = current_raw; 
	while(i < y)
	{   
		pthread_mutex_lock (&lock);
   	i = current_raw;
		current_raw++;
   	pthread_mutex_unlock (&lock);
   	
   	if(i >= y)
			break;
		
		
   	for(int j = 0; j < x ; j++) 
   	{
   		int sum = 0;
 	 		for(int k = 0; k < xMatrix1; k++) 
 	 			sum = sum + (matrix1[k][i] * matrix2[j][k]);
 	 		
 	 		result[j][i]=sum;
 	 		
  		}

	}
	pthread_exit(0);
} 

void printMatrix(char* name, int x, int y, int ** matrix) 
{
	printf("%s",name);
	for( int i = 0; i < y; i++ )
	{
  		printf("\n");
  		for( int j = 0; j < x; j++ )
		  	printf("%d ",matrix[j][i]);
 	}
 	printf("\n");
}


int main( int argc, char* argv[] ) 
{

	void* retval;
	void* arg;
	printf("Give height, width of 1. and 2. matrix and number of threads\n");
	scanf("%d%d%d%d%d", &yMatrix1, &xMatrix1, &yMatrix2, &xMatrix2, &numberOfThreads);	
	
	if( xMatrix1 != yMatrix2) 
	{
		printf("Invalid data\n");
		return 0;
	}
	
	threads = malloc(numberOfThreads * sizeof(pthread_t));
	fillMatrixes();
	current_raw = 0;
	
 	for( int i = 0; i < numberOfThreads; i++ )
   {
      pthread_create(&threads[i], NULL, multiply, (void *) arg );
   } 
	
	for( int i = 0; i < numberOfThreads; i++ )
   {
      pthread_join(threads[i], &retval);
   }

	printMatrix("matrix 1",xMatrix1,yMatrix1,matrix1);
	printMatrix("matrix 2",xMatrix2,yMatrix2,matrix2);
	printMatrix("result",xMatrix2,yMatrix1,result);
	
	free(threads);
	free(matrix1);
	free(matrix2);
	free(result);
	
	return 0;
}


