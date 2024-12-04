#include <stdio.h>
void reset(int *arr){
	for (int i=0;i<20;i++) arr[i]=0;
}
long min(long *arr){
	long m=arr[0];
	for (int i=1;i<20;i++) if (m>arr[i]) m=arr[i];
	return m;
}
int main(){
	FILE *f=fopen("day5.txt","r");
	long ans[20],end,start,range,diff;
	int solved[20],i;
	fscanf(f,"seeds:");
	for (i=0;i<20;i++){
		fscanf(f," %ld",&ans[i]);
	}
	reset(solved);
	while(fscanf(f," %*[^:]:")>-1){
		while(fscanf(f," %ld %ld %ld",&end,&start,&range)>0){
			diff=end-start;
			for (i=0;i<20;i++) if (solved[i]==0 && ans[i]>=start && ans[i]<start+range){
				ans[i]+=diff;
				solved[i]=1;
			}
		}
		reset(solved);
	}
	printf("%ld\n",min(ans));
	return 0;
}
