#include <stdio.h>
#include <time.h>
typedef struct hand{
	char cards[5];
	int bid;
	long score;
	char type[20];
	int tnum;
} hand;
int value(char c){
	char set[13]="J23456789TQKA";
	for (int i=0;i<13;i++) if (c==set[i]) return i;
	return -1;
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
void sortHands(hand h[1000], int length){
    hand t;
    int index;
	int tnumj, tnummin, scorej, scoremin;
    for (int i=0;i<length;i++){
        index=i;
        for (int j=i+1;j<length;j++){
			tnumj=h[j].tnum;tnummin=h[index].tnum;scorej=h[j].score;scoremin=h[index].score;	
            if (tnumj<tnummin || tnumj==tnummin && scorej<scoremin) index=j;
        }
        t=h[i];
        h[i]=h[index];
        h[index]=t;
    }
}

long power(int n,int p){
	long m=1;
	while (p--) m*=n;
	return m;
}
void write(char d[20], char s[20]){
	int i;
	for (i=0; i<20 && s[i];i++) d[i]=s[i];
	if (i<20) d[i]=0;
}
long score(char c[5],int *tnum){
	char d[5];
	int arr[2]={0,0};
	int len=0,index=0,n;
    long result=0;
	for (n=0;n<5;n++){
        d[n]=c[n];
    }
	for (n=0;n<5;n++){ 
        result+=value(d[n])*power(14,4-n);
    }	
	sortCards(d);
	for (n=1;n<6;n++){
		if (n<5 && d[n]=='J') {if (arr[1]>arr[0]) arr[1]++; else arr[0]++;}
		else if (n<5 && d[n]==d[n-1]) len++;
		else {
			if(len) arr[index++]+=len;
			len=0;
		}
	}
	if (arr[1]>arr[0]){
		n=arr[0];
		arr[0]=arr[1];
		arr[1]=n;
	}
	*tnum=arr[0]+arr[1]+((arr[0]>1)? ((arr[0]>2)?2:1):0);
    return result;
}
int main(){
	clock_t start, end;
    double cpu_time_used;
     
    start = clock();

	FILE *f=fopen("day7.txt","r");
	char types[7][20]={
        "High Card",		//0 0 = 0 0
        "One Pair",			//1 0 = 1 1
		"Two Pairs",		//1 1 = 2 2
        "Three of a Kind",	//2 0 = 2 3
		"Full House",		//2 1 = 3 4
        "Four of a Kind",	//3 0 = 3 5
        "Five of a Kind",	//4 0 = 4 6
    };
	hand hands[1001];
	long total=0;
	int i,l=0;
	while (fscanf(f," %s %d", hands[l].cards, &hands[l].bid)>0){
		hands[l].score=score(hands[l].cards,&hands[l].tnum);
		write(hands[l].type,types[hands[l].tnum]);
		l++;	
	}
	sortHands(hands,l);
//	for (i=0;i<l;i++) printf("Index: %d Hand: %s Bid: %d Score: %ld %s %d\n",i,hands[i].cards,hands[i].bid,hands[i].score,hands[i].type,hands[i].tnum);
	for (i=0;i<l;i++) total+=hands[i].bid*(i+1);
	printf("Answer: %ld\n",total);
	
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lfs\n",cpu_time_used);
	return 0;
}
