#include <stdio.h>
int main(){
	FILE *fp= fopen("1.txt","r");
	char line[15];
	int max=100000,c=0,i,j;
	int one[max]={},two[max]={};
	//for (int x=0;x<max;x++) {one[x]=0;two[x]=0;}
	while (fscanf(fp,"%d   %d",&i,&j)>0){
		one[i]+=1;
		two[j]+=1;
		//printf("\na=%d b=%d",a,b);
	}
	i=fclose(fp)-1;
	while(++i<max){ 
		if(one[i]) c+=i*two[i]*one[i];
	}
	printf("total=%d\n",c);
	return 0;
}
