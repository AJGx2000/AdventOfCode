#include <stdio.h>
int main(){
	FILE *f=fopen("day15.txt","r");
	char term[10];
	int sum=0,curr;
	while(fscanf(f,"%[^,\n],",term)>0){
	curr=0;
	for (int i=0;term[i];i++) curr=((curr+term[i])*17)%256;
	sum+=curr;
	}
	printf("Answer %d\n",sum);
	return 0;
}
