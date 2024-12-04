#include <stdio.h>
int main(){
	FILE *f=fopen("day14.txt","r");
	char size=100,avail[size],plat[size][size+1],cont=1;//found input to be 100x100 square before hand using wc
	int sum=0,/* cycles,*/ load[1000],li=0;
	for (int i=0;i<size;i++) fscanf(f,"%s",plat[i]);
//	for (int i=0;i<size;i++) printf("%s\n",plat[i]);
//	puts("\nup");
//	puts("enter num cycles:");
//	scanf("%d",&cycles);
//	for (int cycle=0;cycle<cycles;cycle++){
	while(cont){
//up
		for (int i=0;i<size;i++)avail[i]=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) {
//			old[i][j]=plat[i][j];
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[avail[j]++][j]='O';
//			avail[j]+=1;
			}
			else if (plat[i][j]=='#') avail[j]=i+1;
		}
//		for (int i=0;i<size;i++) printf("%s\n",plat[i]);
//	    puts("\nleft");
//left
		for (int i=0;i<size;i++)avail[i]=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) {
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[i][avail[i]++]='O';
//			avail[i]+=1;
			}
			else if (plat[i][j]=='#') avail[i]=j+1;
		}
//		for (int i=0;i<size;i++) printf("%s\n",plat[i]);
//	    puts("\ndown");
//down
		for (int i=0;i<size;i++)avail[i]=size-1;
		for (int i=size-1;i>=0;i--) for (int j=0;j<size;j++) {
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[avail[j]--][j]='O';
//			avail[j]-=1;
			}
			else if (plat[i][j]=='#') avail[j]=i-1;
		}
//		for (int i=0;i<size;i++) printf("%s\n",plat[i]);
//	    puts("\nright");
//right
		for (int i=0;i<size;i++)avail[i]=size-1;
	    for (int i=0;i<size;i++) for (int j=size-1;j>=0;j--) {
			if (plat[i][j]=='O'){
		        plat[i][j]='.';
	            plat[i][avail[i]--]='O';
//          avail[i]-=1;
			}
		    else if (plat[i][j]=='#') avail[i]=j-1;
	    }
//		for (int i=0;i<size;i++) printf("%s\n",plat[i]);
		sum=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) if (plat[i][j]=='O') sum+=size-i;
		load[li++]=sum;
		for(int i=li-2;i>=0;i--) if (load[i]==load[li-1]){
			if(2*i-li+1>=0 && load[i]==load[2*i-li+1]) {printf("Answer: %d\n",load[i+(1000000000-i)%(li-1-i)-1]);cont=0;}
			else break;
		}
//		printf("%d Answer: %d\n",cycle,sum);
	}
	return 0;
}
