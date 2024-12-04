#include <stdio.h>
#include <time.h>
typedef struct location{
	int x,y,d; //x coord,y coord,current distance
	char p; //current pipe
} location;
int move(location *l, char m[140][142], int w, int h){
	char n; //next;
	//printf("Old Coords (%d,%d)\t Previous Pipe: %c\t Distance: %d\n",l->x,l->y, l->p, l->d);
	//LEFT
	if ((l->p == '-' || l->p == 'J' || l->p == '7' || l->p== 'S') && l->x-1>-1 && (n=m[l->y][l->x-1]) && (n=='-' || n=='L' || n=='F')) {
		m[l->y][l->x]='<';
		l->x-=1;
		l->d++;
		l->p=n;
		m[l->y][l->x]='X';
	}
	//RIGHT
	else if ((l->p == '-' || l->p == 'L' || l->p == 'F' || l->p== 'S') && l->x+1<w && (n=m[l->y][l->x+1]) && (n=='-' || n=='J' || n=='7')) {
            m[l->y][l->x]='>';
			l->x+=1; 
            l->d++;
            l->p=n;
			m[l->y][l->x]='X';
	}
	//UP
	else if ((l->p == '|' || l->p == 'L' || l->p == 'J' || l->p== 'S') && l->y-1>-1 && (n=m[l->y-1][l->x]) && (n=='|' || n=='F' || n=='7')) {
            m[l->y][l->x]='A';
			l->y-=1;
            l->d++;
            l->p=n;
			m[l->y][l->x]='X';
    }
	//DOWN
	else if ((l->p == '|' || l->p == 'F' || l->p == '7' || l->p== 'S') && l->y+1<h && (n=m[l->y+1][l->x]) && (n=='|' || n=='L' || n=='J')) {
            m[l->y][l->x]='V';
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
	clock_t start, end;
    double cpu_time_used=0;
    int loops;
    puts("How many loops for average: ");
    scanf("%d",&loops);
    long answer;
    for (int loop=0;loop<loops;loop++){
    start = clock();


	FILE *f=fopen("day10.txt","r");
	char maze[140][142],curr,last,al,bl;//above and below last
	int width=0,height=0,clockwise,I=0,O=0;
	location l,s;
	while (fscanf(f," %s",maze[height++])>0);
	height-=1;
	while(maze[0][width++]);
	width-=1;
	if (loop==0){//time
	for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) printf("%c",maze[y][x]);
        puts("");
    }
	printf("height: %d\twidth: %d\n",height,width);
	printf("\n\n********************************************************************************************************************************\n\n");
	}//time
	for (int y=0;y<height;y++) for (int x=0;x<width;x++) if (maze[y][x]=='S'){
		l.x=x;s.x=x;
		l.y=y;s.y=y;
		l.d=0;
		l.p='S';
		break;
	}
	while(move(&l,maze,width,height));
	if (s.x>l.x) maze[l.y][l.x]='>';
	else if (s.x<l.x) maze[l.y][l.x]='<';
	else if (s.y>l.x) maze[l.y][l.x]='A';
	else maze[l.y][l.x]='V';
	for (int y=0;y<height;y++) {
		for (int x=0;x<width;x++){
			curr=maze[y][x];
			if (curr!='A' && curr!='V' && curr!='>' && curr!='<') maze[y][x]=(curr='.');
			if (loop==0) printf("%c",curr);//time
		}
		if (loop==0) puts("");//time
	}
	for (int y=0;y<height;y++){
		for (int x=0;x<width;x++){
			curr=maze[y][x];
			if (curr=='A' ||  curr=='V') last=curr;
			else if(curr=='.') last=0;
		}
		if (last) {
			clockwise=(last=='V'?1:0);
			break;
		}
	}
	if (loop==0) printf("%s\n",clockwise?"Clockwise":"Counterclockwise");
//	printf("L1 distance = %d\tL2 distance = %d\n",l1.d,l2.d);
	for (int y=0;y<height;y++) {
		last=0;
		for (int x=0;x<width;x++){
			curr=maze[y][x];
			if (curr!='.'){
				last=curr;
				al=(bl=0);
				if (y>0) al=maze[y-1][x];
				if (y<height-1) bl=maze[y+1][x];
			}
			else if (curr=='.'){
				if (!last || y==0 || y>0 && maze[y-1][x]=='O'|| last!='I' && (clockwise && (last=='V' || last=='<' && bl!='A') || !clockwise && (last=='A' || last=='<' && al!='V' ))){
					maze[y][x]='O';
					last=0;
					O++;
				}
				else {
					last=(maze[y][x]='I');
					I++;
				}
			}
		}
	}
	if (loop==0){ //time
	for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) printf("%c",maze[y][x]);
        puts("");
    }
	printf("I: %d\tO: %d\n",I,O);
	} //time

	end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
    answer+=I;
	fclose(f);
    }
    printf("Answer: %ld\n\n",answer/loops);
	printf("For %d loop%s:\n",loops,loops!=1?"s":"");
    printf("Average Time: %lfs\n",cpu_time_used/loops);
	printf("Total Time: %02d:%02d:%05.2lf\n",(int)(cpu_time_used/3600),(int)(cpu_time_used/60)%60,cpu_time_used-cpu_time_used/60);
	return 0;
}
