#include <stdio.h>
int main(){
	FILE *f=fopen("day11.txt","r");
	char space[140][142];
	int emptyY[140],emptyX[140],width,height=0,galaxies[600][2],gi=0,total=0,expansion=1;
	fscanf(f,"%s",space[0]);
	for (int i=0;i<140;i++) emptyY[i]=(emptyX[i]=1);
	for (width=0;space[0][width];width++) if (space[0][width]=='#') {
		emptyY[0]=(emptyX[width]=0);
		galaxies[gi][0]=0;
		galaxies[gi++][1]=width;
	}
	while(fscanf(f,"%s",space[++height])>0){
		for (int x=0;x<width;x++) if (space[height][x]=='#') {
			emptyY[height]=(emptyX[x]=0);
			galaxies[gi][0]=height;
			galaxies[gi++][1]=x;
		}
	}
	/*
	printf("  ");
	for (int i=0;i<width;i++) printf("%d",emptyX[i]); puts("");
	for (int i=0;i<height;i++) printf("%d %s\n",emptyY[i],space[i]);
	*/
	for (int i=0;i<gi-1;i++){
		for (int j=i+1;j<gi;j++){
			total+=galaxies[j][0]-galaxies[i][0];
			for (int y=galaxies[i][0];y<galaxies[j][0];y++) if (emptyY[y]) total+=expansion;
			if (galaxies[j][1]<galaxies[i][1]) {
				total += galaxies[i][1]-galaxies[j][1];
				for (int x=galaxies[j][1];x<galaxies[i][1];x++) if (emptyX[x]) total+=expansion;
			}
			else {
				total += galaxies[j][1]-galaxies[i][1];
				for (int x=galaxies[i][1];x<galaxies[j][1];x++) if (emptyX[x]) total+=expansion;
			}
//			printf("G1: y:%d x:%d\tG2: y:%d x:%d\ttotal=%d\n",galaxies[i][0],galaxies[i][1],galaxies[j][0],galaxies[j][1],total);
		}
	}
	printf("Answer: %d\n",total);
	return 0;
}
