#include <stdio.h>
typedef struct hand{
	char cards[5];
	int bid;
	long score;
	char type[20];
	int tnum;
} hand;
int value(char c){
	char set[13]="23456789TJQKA";
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
void sortHands(hand h[1000], int length){//1000]){
    hand t;
    int index;
	int tnumj, tnummin, scorej, scoremin;
    for (int i=0;i<length;i++){//1000
        index=i;
        for (int j=i+1;j<length;j++){//1000
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
/*
long score(char c[5]){
	int same=0,cards=4;
	long result=0;
	for (int i=1;i<6;i++){
		if (i<5 &&  c[i]==c[i-1]){
			same++;
			cards--;
		}
		else {
			result+=value(c[i-1])*power(100,same);
			same=0;
		}
	}
	return result*power(10,4-cards);
}
*/
void write(char d[20], char s[20]){
	int i;
	for (i=0; i<20 && s[i];i++) d[i]=s[i];
	if (i<20) d[i]=0;
	//printf("Source: %s | Destination: %s\n",s,d);
}
long score(char c[5],char t[20],int *tnum){
	char d[5],types[7][20]={
		"High Card",
		"One Pair",
		"Two Pairs",
		"Three of a Kind",
		"Full House",
		"Four of a Kind",
		"Five of a Kind"
	};
	for (int i=0;i<5;i++){
		d[i]=c[i];
	}
	int arr[2]={0,0};
	int len=0,index=0;
    long result=0,base=power(13,4);
	for (int i=0;i<5;i++){
        //if (i<5 &&  c[i]==c[i-1]) cards--;
        result+=value(d[i])*power(14,4-i);
    }
	sortCards(d);
	for (int i=1;i<6;i++){
		if (i<5 &&  d[i]==d[i-1]) len++;
		else {
//			printf("%s %d %d %d\n",c,len,count, len*2-(len?count:0));
//			result*=power(14,5+len*2-(len?count:0));
			if (len) arr[index++]=len;
			len=0;
		}
	}
	//for(int j=0;j<7;j++) printf("%s\n",types[j]);
	if (arr[0]==1 && arr[1]==0) {write(t,types[1]); *tnum=1;}
	else if (arr[0]==1 && arr[1]==1) {write(t,types[2]); *tnum=2;}
	else if (arr[0]==2 && arr[1]==0) {write(t,types[3]); *tnum=3;}
	else if (arr[0]==2 && arr[1]==1 || arr[0]==1 && arr[1]==2) {write(t,types[4]);  *tnum=4;}
	else if (arr[0]==3 && arr[1]==0) {write(t,types[5]); *tnum=5;}
	else if (arr[0]==4 && arr[1]==0) {write(t,types[6]); *tnum=6;}
	else {write(t,types[0]); *tnum=0;}
//	printf("THE GODDAMN TYPE: >%s< %ld\n",t,t);
    return result;//*(power(14,arr[0])+power(14,arr[1])) *(arr[0]&&arr[1]? 7:1);
}
int main(){
	FILE *f=fopen("day7.txt","r");
	hand hands[1000];
	long total=0;
	int i,l=0;
	while (fscanf(f," %s %d", hands[l].cards, &hands[l].bid)>0){
		hands[l].score=score(hands[l].cards,hands[l].type,&hands[l].tnum);
//		printf("Type> %s <",hands[l].type);
		l++;
	}
	for (i=0;i<l;i++) printf("%s %d %ld\n",hands[i].cards,hands[i].bid,hands[i].score);
	sortHands(hands,l);
	puts("SORTING");
	for (i=0;i<l;i++) printf("%s %d %ld %d %s %d\n", hands[i].cards, hands[i].bid, hands[i].score, i+1, hands[i].type, hands[i].tnum);
	for (i=0;i<l;i++) total+=hands[i].bid*(i+1);
	printf("Answer: %ld\n",total);
	return 0;
}
