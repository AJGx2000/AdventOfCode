#include <stdio.h>
#include <time.h>
typedef struct map{
	long end;
	long start;
	long range;
	long diff;
} map;
long min(long *arr){
	long m=arr[0];
	for (int i=1;i<20;i++) if (m>arr[i]) m=arr[i];
	return m;
}
long max(map m){
	return m.start+m.range;
}
int inRange(map m, map n){
	return n.start>=m.start && n.start<m.start+m.range;
}
void quickSort(map *arr, int size){
	map swap;
	int min;
	for (int i=0;i<size;i++){
		min=i;
		for (int j=i+1;j<size;j++) if (arr[min].start>arr[j].start) min=j;
		swap=arr[i];
		arr[i]=arr[min];
		arr[min]=swap;
	}
}
int main(){
	clock_t start, end;
    double cpu_time_used; 
    start = clock();

	FILE *f=fopen("day5.txt","r");
	int i,j,k;
	int lengths[7],lenseeds=10;
	map all[7][50],seeds[125];
	long diff;
	fscanf(f,"seeds:");
	for (i=0;i<lenseeds;i++) fscanf(f," %ld %ld",&seeds[i].start,&seeds[i].range);
	quickSort(seeds,lenseeds);
	for (i=0;i<7;i++){
		fscanf(f," %*[^:]:");
		j=0;
		while (fscanf(f," %ld %ld %ld\n",&all[i][j].end,&all[i][j].start,&all[i][j].range)>0){
			all[i][j].diff=all[i][j].end-all[i][j].start;
			j++;
		}
		quickSort(all[i],j);
		lengths[i]=j;
	}
	//printf("after maplist %d:\n",0);
    //for (j=0;j<lengths[0];j++) printf("%ld.) start: %ld range: %ld\n",j,all[0][j].start,all[0][j].range);
    //puts("\n");
	for (i=0;i<7;i++){
		for (k=0;k<lenseeds;k++){
			j=0;
			while(j<lengths[i] && !inRange(all[i][j],seeds[k]) && seeds[k].start>=all[i][j].start) j++;
			if (j<lengths[i] && !(seeds[k].start<all[i][j].start)){
				diff=max(seeds[k])-max(all[i][j]);
				if (diff>0){
	//				printf("ans:(%ld, %ld) map:(%ld, %ld) diff=%ld\n",all[0][k].start,all[0][k].range,all[i][j].start,all[i][j].range,diff);
                    seeds[lenseeds].start=seeds[k].start;
					seeds[lenseeds].range=seeds[k].range;
                    seeds[k].range-=diff;
                    seeds[lenseeds].range=diff;
                    seeds[lenseeds++].start=max(seeds[k]);
				}
				seeds[k].start+=all[i][j].diff;
			}
		}
		quickSort(seeds,lenseeds);
	//	printf("after maplist %d:\n",i);
	//	for (j=0;j<lengths[0];j++) printf("%ld.) start: %ld range: %ld\n",j,all[0][j].start,all[0][j].range);
	//	puts("\n");
	}
	printf("Answer: %ld\n",seeds[0].start);	
	end=clock();
	cpu_time_used=((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lfs\n",cpu_time_used);
	return 0;
}
