#include<stdio.h>
#include<stdbool.h>

_Bool f(int czarny, int bialy,int tab[1297][5],int j,int i)
{
 int pomoc[5];
 int b=0;
 int c=0;
 
 for(int k=1;k<=4;k++)
	 pomoc[k]=tab[i][k];

 for(int z=1;z<=4;z++)
	 if(pomoc[z]==tab[j][z])
	  c=c+1;


 for(int z=1; z<=4;z++)
 	for(int h=1;h<=4;h++)
		if(pomoc[h]==tab[j][z])
			{
	   	 b++;
			 pomoc[h]=0;
			 break;
			}		
 b=b-c;
 if(b==bialy && c==czarny)
	return true;

 return false;
}


int main()
{
 int czarny,bialy; 
 int tab[1297][5];
 
 for(int i=0;i<1296;i++)
 	tab[i][0]=1;
 for(int i=0;i<1296;i++)
	 tab[i][1]=(i/216)+1;	 
 for(int i=0;i<1296;i++)
	 tab[i][2]=((i/36))%6+1;		
 for(int i=0;i<1296;i++)
	 tab[i][3]=(i/6)%6+1;		 	
 for(int i=0;i<1296;i++)
	 tab[i][4]=i%6+1;


 for(int i=0;i<1296;i++)
 	{
  	 if(tab[i][0]==0)
  	 continue;
 	 printf("[%d] [%d] [%d] [%d]?\n",tab[i][1],tab[i][2],tab[i][3],tab[i][4]);
 	 printf("white: ");
 	 scanf("%d",&bialy);
 	 printf("black: ");
 	 scanf("%d",&czarny);			
	 if(czarny==4) 
		{
		 printf("I win\n");
		 return 0;
 		}
 	
 	 for(int j=0;j<1296;j++)
 		if(f(czarny,bialy,tab,j,i)==false)
 			tab[j][0]=0;			

	 i=0; 
	}
		
printf("you are cheating!\n");
return 0;
}
