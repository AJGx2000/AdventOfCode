#include <stdio.h>
int main(){
	FILE *f = fopen("day2.txt","r");
	char line[200],type=0;
	int total=0,game=0,num=0,r=2,g=1,b=0,index=0;
	int arr[3]={0,0,0};
	while (fscanf(f,"Game %d: ",&game)>0){
		while (fscanf(f,"%d %c%*s ",&num,&type)>0){
			index=type=='g'?g:(type>'g'?r:b);
			if (num>arr[index]) {
				arr[index]=num;
			}
		}
		num=1;
		for (int i=0;i<3;i++){
			num*=arr[i];
			arr[i]=0;
		}
		total+=num;
	}
	printf("%d\n",total);
	return 0;
}
