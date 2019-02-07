#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<linux/limits.h>
char *convert(unsigned int num, int base) 
{ 
	static char Representation[]= "0123456789abcdef";
	static char buffer[50]; 
	char *ptr; 
	
	ptr = &buffer[49]; 
	*ptr = '\0'; 
	
	do 
	{ 
		*--ptr = Representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	
	return(ptr); 
}
void myprintf(char* type,...) 
{ 
	char *traverse; 
	int i; 
	int j=0;
	char *temp = (char*)&type + sizeof (type);


	for(traverse = type; j<strlen(type); traverse++,j++) 
	{ 
		while( *traverse != '%' &&  *traverse !='\0' ) 
		{ 
			write(1,traverse,1);
			traverse++; 
			j++;
		} 	
		traverse++; 					
		j++;
		if(*traverse == 'd')	{	
			i = *((int *)temp);
			temp = temp + sizeof (int);
			if(i<0) { 
			i = -i;
			write(1,(void *)'-',1); 
			} 
		
			write(1,(void *)convert(i,10),strlen(convert(i,10)));
		}
		
		else if(*traverse == 'b') {
			i = *((int *)temp);
			temp = temp + sizeof (int);
			write(1,(void *)convert(i,2),strlen(convert(i,2)));	
			}
				
		else if(*traverse == 'x')	{
			i = *((int *)temp);
			temp = temp + sizeof (int);
			write(1,(void *)convert(i,16),strlen(convert(i,16)));
		}
		
		else if(*traverse == 's')	{
			char* ch = *((char**) temp);
			while(ch[0]!='\0') {
				write(1,ch,sizeof (char));
				ch++;
			}
			
			temp = temp + sizeof (char *);				
		}
		j++;
	}
	return;
} 

void myscanf(char type, void* aim) {
	
	char buf[1024] ;
	char ch;
	int intResult=0;
	int i=0;
	
	if(type == 's') {
		while (read(1,&ch,1) > 0 && ch !='\n') {
		*(char*)(aim+i) = ch;
		i++;
		}
		*(char*)(aim+i) = '\0';
		return;
	}
	
	while (read(1,&ch,1) > 0 && ch !='\n') {
		buf[i] = ch;
		i++;
	}
	
	i--;
	int length = i;

	if(type == 'd') {
		while(i>=0) {
			intResult = intResult + pow(10,length-i)*(buf[i] - '0');
			i--;
		}
		 *(int* )aim = intResult;
	}
	
	else if(type == 'x') {
		while(i>=0) {
			if(buf[i]>58)
				intResult = intResult + pow(16,length-i)*(buf[i] - 87);
			else	
				intResult = intResult + pow(16,length-i)*(buf[i] - '0');
		 	i--;
		 }
		 *(int* )aim = intResult; 
	}
	
	else if(type == 'b') {
			while(i>=0) {
				intResult = intResult + pow(2,length-i)*(buf[i] - '0');
		 	i--;
		 }
		 *(int* )aim = intResult;
	}
	
	return;
}


int main() {
	int e,f,g;
	char* s;
	s=malloc(20);
	myprintf("TEST\ngive 1 string, 1 dec, 1 hex, 1 bin\n");

	myscanf('s',s);
	myscanf('d',&e);
	myscanf('x',&f);
	myscanf('b',&g);

	myprintf("You entered :\nstring = %s\ndec = %d\nhex= %x\nbin= %b%\n",s,e,f,g);

	return 0;
}


