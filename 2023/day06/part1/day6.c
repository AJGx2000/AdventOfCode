#include <stdio.h>
int main(){
	FILE *f=fopen("day6.txt","r");
	int arr[2][4];
	int i,j,counter,total=1;
	for (i=0;i<2;i++){
		fscanf(f,"%*s");
		for (j=0;j<4;j++) fscanf(f," %d",&arr[i][j]);
	}
	for (i=0;i<4;i++){
		counter=0;
		for (j=0;j<=arr[0][i];j++) if (j*(arr[0][i]-j)>arr[1][i]) counter++;
		total*=counter;
	}
	printf("Answer: %d\n",total);
	return 0;
}
