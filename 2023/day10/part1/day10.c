#include <stdio.h>
typedef struct location{
	int x,y,d; //x coord,y coord,current distance
	char p; //current pipe
} location;
int move(location *l, char m[140][142], int w, int h){
	char n; //next;
	//printf("Old Coords (%d,%d)\t Previous Pipe: %c\t Distance: %d\n",l->x,l->y, l->p, l->d);
	//LEFT
	if ((l->p == '-' || l->p == 'J' || l->p == '7' || l->p== 'S') && l->x-1>-1 && (n=m[l->y][l->x-1]) && (n=='-' || n=='L' || n=='F')) {
		l->x-=1;
		l->d++;
		l->p=n;
		m[l->y][l->x]='X';
	}
	//RIGHT
	else if ((l->p == '-' || l->p == 'L' || l->p == 'F' || l->p== 'S') && l->x+1<w && (n=m[l->y][l->x+1]) && (n=='-' || n=='J' || n=='7')) {
            l->x+=1; 
            l->d++;
            l->p=n;
			m[l->y][l->x]='X';
	}
	//UP
	else if ((l->p == '|' || l->p == 'L' || l->p == 'J' || l->p== 'S') && l->y-1>-1 && (n=m[l->y-1][l->x]) && (n=='|' || n=='F' || n=='7')) {
            l->y-=1;
            l->d++;
            l->p=n;
			m[l->y][l->x]='X';
    }
	//DOWN
	else if ((l->p == '|' || l->p == 'F' || l->p == '7' || l->p== 'S') && l->y+1<h && (n=m[l->y+1][l->x]) && (n=='|' || n=='L' || n=='J')) {
            l->y+=1;
            l->d++;
            l->p=n;
			m[l->y][l->x]='X';
    }
	else return 0;
	//printf("New Coords (%d,%d)\t Current Pipe: %c\t Distance: %d\n",l->x,l->y, l->p, l->d);
    return 1;
}
int main(){
	FILE *f=fopen("day10.txt","r");
	char maze[140][142];
	int width=0,height=0;
	location l1,l2;
	while (fscanf(f," %s",maze[height++])>0);
	height-=1;
	while(maze[0][width++]);
	width-=1;
	for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) printf("%c",maze[y][x]);
        puts("");
    }
	printf("height: %d\twidth: %d\n",height,width);
	printf("\n\n********************************************************************************************************************************\n\n");
	for (int y=0;y<height;y++) for (int x=0;x<width;x++) if (maze[y][x]=='S'){
		l1.x=x;l2.x=x;
		l1.y=y;l2.y=y;
		l1.d=0;l2.d=0;
		l1.p='S';l2.p='S';
		break;
	}
	while(move(&l1,maze,width,height) &&  move(&l2,maze,width,height));
	/*{
		printf("L1 (%d,%d)\n",l1.x,l1.y);
		printf("L2 (%d,%d)\n",l2.x,l2.y);
		break;
	}*/
	for (int y=0;y<height;y++) {
		for (int x=0;x<width;x++) printf("%c",maze[y][x]);
		puts("");
	}
	printf("L1 distance = %d\tL2 distance = %d\n",l1.d,l2.d);
	return 0;
}
