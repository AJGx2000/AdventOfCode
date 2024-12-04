#include <stdio.h>
#include <time.h>
typedef struct hand{
	char cards[5];
	int bid;
	long score;
	int tnum;
} hand;
int value(char c){
	char set[4]="AKQT";
	if (c<='9') return c-'0'-1;
	for (int i=0;i<4;i++) if (c==set[i]) return 12-i;
	return 0;
}
void sortCards(char c[5]){
	char t;
	int index;
	for (int i=0;i<5;i++){
		index=i;
		for (int j=i+1;j<5;j++){
			if (value(c[j])>value(c[index])) index=j;
		}
		t=c[i];
		c[i]=c[index];
		c[index]=t;
	}
}
void sortHands(hand hands[1001], int length){
	hand low[length], high[length], pivot;
	int i,j=0,l=0,h=0,half=length/2;
	pivot=hands[half];
	for (i=0;i<length;i++) if (i!=half) {if (hands[i].tnum<pivot.tnum || hands[i].tnum==pivot.tnum && hands[i].score < pivot.score) low[l++]=hands[i]; else high[h++]=hands[i];}
	if (l>1) sortHands(low,l);	
	for (i=0;i<l;i++) hands[j++]=low[i];
	hands[j++]=pivot;
	if (h>1) sortHands(high,h);
	for (i=0;i<h;i++) hands[j++]=high[i];
	return;
}
long score(char c[5],int *tnum){
	char d[6];
	int arr[2]={0,0};
	int len=0,index=0,n;
    long result=0;
	for (n=0;n<5;n++){
        d[n]=value(c[n]);
    }
	d[5]=13;
	result=d[0]*28561+d[1]*2197 +d[2]*169 +d[3]*13+d[4];
	sortCards(d);
	for (n=1;n<6;n++){
		if (d[n]==0) arr[0]++;
		else if (d[n]==d[n-1]) len++;
		else {
			if(len) arr[index++]+=len;
			len=0;
		}
	}
	if (arr[1]==2){
		arr[0]=2;
		arr[1]=1;
	}
	*tnum=arr[0]+arr[1]+((arr[0]>1)? ((arr[0]>2)?2:1):0);
    return result;
}
int main(){
	clock_t start, end;
    double cpu_time_used;
	long total=0;
	int loops=1000;
	for (int test=0;test<loops;test++){
    start = clock();

	FILE *f=fopen("day7.txt","r");
	hand hands[1001];
	//long total=0;
	int i,l=0;
	while (fscanf(f," %s %d", hands[l].cards, &hands[l].bid)>0){
		hands[l].score=score(hands[l].cards,&hands[l].tnum);	
		l++;	
	}
	sortHands(hands,l);
//	for (i=0;i<l;i++) printf("Hand: %s Bid: %d Score: %ld %d\n",hands[i].cards,hands[i].bid,hands[i].score,hands[i].tnum);
	for (i=0;i<l;i++) total+=hands[i].bid*(i+1);
	//printf("Answer: %ld\n",total);
	
	end = clock();
	fclose(f);
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	printf("Answer: %ld\n",total/loops);
	printf("Average Time: %lfs\n",cpu_time_used/loops);
	return 0;
}
