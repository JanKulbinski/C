#include<stdio.h>
#include<stdbool.h>
#include<string.h>

_Bool match(char* wzorzec, char* lancuch)
{
 int w=strlen(wzorzec);
 int l=strlen(lancuch);

 if(((wzorzec[0]==lancuch[0]) || (wzorzec[0]=='?')) && l!=0)
 	{
 	 lancuch++;
 	 wzorzec++;
 	 if(match(wzorzec,lancuch))	
 	 	return true;
 	 else 
 	 	return false;
 	}
 
 if(wzorzec[0]=='*')
 	{
 	 while(wzorzec[0]=='*')
 	 	 wzorzec++;	
 	 w=0;	 	 		 	 	
	 l=strlen(lancuch);
	 lancuch=lancuch+l;
	 while(l-w>=0)		//od tylu zeby gwiazdka pochlonela najwiecej liter jak to mozlie
		{
		 if(match(wzorzec,lancuch))
		 	{
		 	return true;
		 	}
		 l--;
		 lancuch--;
		}	
	} 
 
 if(w==0 && l==0)
 	return true;

 if(wzorzec[0]!=lancuch[0]) 	 
 	 return false;
}



int main()
{
 char wzorzec[100], lancuch[100];
 printf("Podaj wzorzec: ");
 scanf("%s",wzorzec);
 printf("Podaj lancuch: ");
 scanf("%s",lancuch);
 if(match(wzorzec,lancuch))
 	printf("true\n");
 else 
	printf("false\n");
 return 0;
}
