#include <stdio.h>
#include <stdlib.h>
#define size 141
typedef struct node{
	char val,facing,final,x,y,straight;
	int dist;
	struct node *p;
}node;
typedef struct active{
    struct node *p,*c,*n; //prev, curr, next
}node;
int main(){
	FILE *f=fopen("day17test.txt","r");
	node map[size][size+1];
	char buff[size+1];
	int width,height=-1,i=0;
	active *actives=(struct active*)malloc(sizeof(struct active)),*curr;
	fscanf(f,"%s",buff);
	printf("%s\n",buff);
	rewind(f);
	for( width=0;buff[width];width++);
	printf("width %d\n",width);
	while (fscanf(f,"%1[0-9] ",&map[i/width][i%width].val)>0) i++;
	height=i/width;
	for (i=0;i<height;i++) for (int j=0;j<width;j++) {map[i][j].val-='0';map[i][j].dist=0;map[i][j].facing='.';map[i][j].final=0;map[i][j].x=j;map[i][j].y=i;map[i][j].straight=0;map[i][j].p=NULL;}
	printf("height %d\n",height);
	//for (int i=0;i<width;i++) printf("%d ",map[0][i].val);	puts("");
	actives->c=map[0][0];
	while(actives){
		curr=actives;
		while(curr){
			if (curr->c->x>0)
		}
	}
	return 0;
}
