#include <stdio.h>
int main(){
	FILE *f=fopen("day14.txt","r");
	char size=100,avail[size],plat[size][size+1],cont=1;//found input to be 100x100 square before hand using wc
	int load[1000],li=-1;
	for (int i=0;i<size;i++) fscanf(f,"%s",plat[i]);
	while(cont){
//up
		for (int i=0;i<size;i++)avail[i]=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) {
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[avail[j]++][j]='O';
			}
			else if (plat[i][j]=='#') avail[j]=i+1;
		}
//left
		for (int i=0;i<size;i++)avail[i]=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) {
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[i][avail[i]++]='O';
			}
			else if (plat[i][j]=='#') avail[i]=j+1;
		}
//down
		for (int i=0;i<size;i++)avail[i]=size-1;
		for (int i=size-1;i>=0;i--) for (int j=0;j<size;j++) {
			if (plat[i][j]=='O'){
				plat[i][j]='.';
				plat[avail[j]--][j]='O';
			}
			else if (plat[i][j]=='#') avail[j]=i-1;
		}
//right
		for (int i=0;i<size;i++)avail[i]=size-1;
	    for (int i=0;i<size;i++) for (int j=size-1;j>=0;j--) {
			if (plat[i][j]=='O'){
		        plat[i][j]='.';
	            plat[i][avail[i]--]='O';
			}
		    else if (plat[i][j]=='#') avail[i]=j-1;
	    }
		load[++li]=0;
		for (int i=0;i<size;i++) for (int j=0;j<size;j++) if (plat[i][j]=='O') load[li]+=size-i;
		for(int i=li-1;i>=0;i--) if (load[i]==load[li]){
			if(2*i-li>=0 && load[i]==load[2*i-li]) {printf("Answer: %d\n",load[i+(1000000000-i)%(li-i)-1]);cont=0;}
			else break;
		}
	}
	return 0;
}
