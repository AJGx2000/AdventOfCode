#include <stdio.h>
int main(){
	FILE *f = fopen("day9.txt","r");
	int test=0,len=test?6:21; 
	int patterns[len][len],res;//,count=1;
	long total=0;
	while (fscanf(f," %d",&patterns[0][0])>0){
		for (int i=1;i<len;i++){
			fscanf(f," %d",&patterns[0][i]);
			for (int j=1;j<=i;j++){
				patterns[j][i-j]=patterns[j-1][i-j+1]-patterns[j-1][i-j];
			}
		}
//		for (int i=0;i<len;i++){
//			printf("%*s",i*2,"");
//			for (int j=0;j<len-i;j++) printf("%02d  ",patterns[i][j]);
//			puts("");
//		}
//		printf("%d\n",patterns[len-1][0]);
		res=patterns[len-1][0];
		for (int i=1;i<len;i++) {
//			printf("%d.) %d-%d=",len-i,patterns[len-1-i][0],res);
			res=patterns[len-1-i][0]-res;
//			printf("%d\n",res);
		}
//		printf("%d.) %d\n",count++,res); 
		total+=res;
	}
	printf("Answer: %ld\n", total);
	return 0;
}
