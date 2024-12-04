#include <stdio.h>
int main(){
	FILE *f = fopen("day9.txt","r");
	int patterns[21][2];
	long total=0,max;
	while (fscanf(f," %d",&patterns[0][1])>0){
		max=21;
		for (int i=1;i<21;i++){
			patterns[0][0]=patterns[0][1];
			fscanf(f," %d",&patterns[0][1]);
			for (int j=1;j<=i && j<max;j++){
				patterns[j][0]=patterns[j][1];
				patterns[j][1]=patterns[j-1][1]-patterns[j-1][0];
				if (patterns[j-1][0]==0 && patterns[j-1][1]==0 && patterns[j][0]==0 && patterns[j][1]==0) max=j;
			}
		}
		for (int i=0;i<max;i++) total+=patterns[i][1];
	}
	printf("Answer: %ld\n", total);
	return 0;
}
