#include <stdio.h>
int main(){
	FILE *f=fopen("day14.txt","r");
	char size=100,available[size],line[size+1];//found input to be 100x100 square before hand using wc
	int sum=0;
	for (int i=0;i<size;i++)available[i]=0;
	for (int i=0;i<size;i++){
		fscanf(f,"%s",line);
		for (int j=0;j<size;j++){
			if (line[j]=='O'){
				sum+=size-available[j];
				available[j]+=1;
			}
			else if (line[j]=='#') available[j]=i+1;
		}
	}
	printf("Answer: %d\n",sum);
	return 0;
}
