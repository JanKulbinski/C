#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char **argv) {
	
	char location[1024];
	char line[1024];
	char *firstCommand;
	char lastChar;
	char *command[100];
	int lineLength;
	bool inBackground = false;
	int status;
	
	printf("\n");

	while(1) {

	
		pid_t temp;

		getcwd(location,1024);
		printf("\033[38;5;1muser@:\033[38;5;4m%s\033[0m$",location);
		lineLength = 0;
		
		while( (lastChar = getchar()) != EOF && lastChar != '\n' && lineLength < 1023 )  {
			line[lineLength] = lastChar;
			lineLength++;
		}
		
		if ( lineLength != 0 && line[lineLength-1] == '&' ) {
			inBackground = true;
			line[lineLength-1] = '\0';
		}
		else {
			line[lineLength] = '\0';
			
		}
		firstCommand = strtok(line," ");		
		
		if( lastChar == EOF || ( firstCommand != NULL && (strcmp(firstCommand,"exit") == 0) ) ) {
			printf("BY !\n");
			return 0;
									
		} else if ( firstCommand != NULL && strcmp(firstCommand,"cd" ) == 0 ) {
				
				char *destination = strtok(NULL," ");
				char newDestination[45];
				if( destination == NULL ) {
					printf("Lack of arrgument\n");
				} else if( strcmp(destination,"..") == 0 ) {
					int i = strlen(location)-1;
					while( i >= 0 ) {
						if( location[i] == '/' ) {
						newDestination[i]='\0';	
							while(i>0) {
								i--;
								newDestination[i]=location[i];
							}
						chdir(newDestination);									
 							break;
						}
						i--;
					}				
				}
				else {
					strcat(location,"/");
					strcat(location,destination);
					chdir(location);
				}
							
		} else if(lineLength != 0){
	
			int j = 0;
			char *word = firstCommand;
			
			while(word!=NULL && j < 100)
			{
				command[j]= word;
				j++;
				word = strtok(NULL," ");
	
			}
			command[j] = NULL;
			
			
			if ( fork() == 0) {

				if ( fork() == 0 ) {	 	
				
					if (execvp(firstCommand, command) == -1) {
						printf("ERROR: %s\n", strerror(errno));
					}
					exit(0); 		 
				}
			
				else if (!inBackground) {
					wait(&status);	
					exit(0);		
				} 
				
				else {
					exit(0);
				}
					
			}
			
			else {
			wait(&status);
			}
			
			inBackground = false;	
		}
	}
	return 0;
}	


