#include <stdio.h>
int min(int* arr,int size){
	int min=999,index=0;
	for (int i=0;i<size;i++){
		if (arr[i]>-1 && arr[i]<min){
			min=arr[i];
			index=i;
		}
	}
	arr[index]=-1;
	return min;
}
void insertionSort(int *temp,int* arr, int size){
	for (int i=0;i<size;i++) arr[i]=min(temp,size);
}
int check(int num,int *arr,int size){
	int i=0;
	while(i<size && num>arr[i])i++;
	return i<size && arr[i]==num;
}
int main(){
	FILE *f=fopen("day4.txt","r");
	int temp10[10],wins[10],temp25[25],nums[25],card,total=0;;
	while(fscanf(f," Card %*d:")>-1){
		card=0;
		for (int i=0;i<10;i++)fscanf(f," %d",&temp10[i]);
		fscanf(f," |");
		for (int i=0;i<25;i++)fscanf(f," %d",&temp25[i]);
	    insertionSort(temp10,wins,10);
		insertionSort(temp25,nums,25);
		for (int i=0;i<25;i++) if (check(nums[i],wins,10)) card+=card?card:1;
		total+=card;
	}
	printf("%d\n",total);
	return 0;
}
