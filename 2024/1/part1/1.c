#include <stdio.h>
int main(){
	FILE *fp= fopen("1.txt","r");
	char line[35];
	int max=100001,c=0,one[max],two[max],i,j;
	for (int x=0;x<max;x++) {one[x]=0;two[x]=0;}
	while (fscanf(fp,"%d   %d",&i,&j)>0){
		one[i]+=1;
		two[j]+=1;
		//printf("\na=%d b=%d",a,b);
	}
	i=(j=0);
	while  (1){
		while(i<max && !one[i++]);
		if (i==max) goto end; 
		while (!two[j++]);
		two[--j]-=1;
	       	one[--i]-=1;	
		c+=i>j?i-j:j-i;
	}
end:
	printf("\n\ntotal=%d\n\n",c);
	return 0;
}