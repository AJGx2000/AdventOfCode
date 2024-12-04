#include <stdio.h>
#include <time.h>
int digits(int n){
	int c=1;
	while ((n=n/10)) c++;
	return c;
}
int power(int n,int p){
	int ans=1;
	while (p--) ans*=n;
	return ans;
}
int main(){
	clock_t start, end;
    double cpu_time_used; 
    start = clock();

	FILE *f=fopen("day6.txt","r");
	int i,j,temp;
	long arr[2]={0,0};
	long total=0;
	for (i=0;i<2;i++){
		fscanf(f,"%*s");
		for (j=0;j<4;j++) {
			fscanf(f," %d",&temp);
//			printf("%d %d %d ",temp,digits(temp),power(10,digits(temp)));
			arr[i]=arr[i]*power(10,digits(temp))+temp;
//			printf("%ld\n",arr[i]);
		}
	}
//	printf("Values: %ld %ld\n",arr[0],arr[1]);
	for (i=0;i<=arr[0];i++) if (i*(arr[0]-i)>arr[1]) total++;
	printf("Answer: %ld\n",total);
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lf\n",cpu_time_used);
	return 0;
}
