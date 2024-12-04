#include <stdio.h>
#include <stdlib.h>
#define size 111
typedef struct beam{
	int id;
	char d,y,x;//direction y/x coords
	struct beam *n,*p; //next previous
	} beam;
int main(){
	FILE *f=fopen("day16.txt","r");
	char map[size][2][size],height=-1,width,c;
	int energized=0,id=0;
	beam *beams=(struct beam*)malloc(sizeof(struct beam)), *curr,*temp;
	beams->id=id++;
	beams->d='>';
	beams->y=0;
	beams->x=-1;
	beams->n=NULL;
	beams->p=NULL;
	while(fscanf(f,"%s ",map[++height][0])>0);
	for (width=0;map[0][0][width];width++);
	printf("width=%d height=%d\n\n",width,height);
	for(int i=0;i<height;i++) for(int j=0;j<width;j++) map[i][1][j]=0;
	for(int i=0;i<height;i++) printf("%s\n",map[i][0]);puts("");
//	for(int i=0;i<height;i++) {for(int j=0;j<width;j++) printf("%d",map[i][1][j]); puts("");}
	while (beams){
		curr=beams;
		while(curr){
//			printf("%4d %4d %1c %1c %4d\t",curr->y,curr->x,map[curr->y][0][curr->x],curr->d,curr->id);
			if (curr->d=='^'){
				curr->y--;
				if (curr->y<0 || map[curr->y][0][curr->x]=='^' || map[curr->y][0][curr->x]=='V'){
//					printf("%13d died\t",curr->id);
			        if (curr->p) curr->p->n=curr->n;
                    else  beams=curr->n;
                    if (curr->n) curr->n->p=curr->p;
					temp=curr;
					curr=curr->n;
                    free(temp);
				}
				else{
					c=map[curr->y][0][curr->x];
					if (map[curr->y][1][curr->x]==0) {energized++;map[curr->y][1][curr->x]=1;}
					if (c=='\\') curr->d='<';
					else if (c=='/') curr->d='>';
					else if (c=='.') map[curr->y][0][curr->x]=curr->d;
					else if (c=='-'){
						curr->d='>';
						temp=(struct beam*)malloc(sizeof(struct beam));
						temp->id=id++;
//						printf("%13d born\t",temp->id);
						temp->d='<';
						temp->y=curr->y;
						temp->x=curr->x;
						temp->n=curr;
						temp->p=curr->p;
						if (curr->p) curr->p->n=temp;
						else beams=temp;
						curr->p=temp;
					}
//					curr=curr->n;
				}
			}
			else if (curr->d=='V'){
                curr->y++;
                if (curr->y>=height || map[curr->y][0][curr->x]=='^' || map[curr->y][0][curr->x]=='V'){
//					printf("%13d died\t",curr->id);
			        if (curr->p) curr->p->n=curr->n;
                    else  beams=curr->n;
                    if (curr->n) curr->n->p=curr->p;
					temp=curr;
                    curr=curr->n;
                    free(temp);

				}
                else{
                    c=map[curr->y][0][curr->x];
                    if (map[curr->y][1][curr->x]==0) {energized++;map[curr->y][1][curr->x]=1;}
                    if (c=='\\') curr->d='>';
                    else if (c=='/') curr->d='<';
                    else if (c=='.') map[curr->y][0][curr->x]=curr->d;
                    else if (c=='-'){
                        curr->d='>';
                        temp=(struct beam*)malloc(sizeof(struct beam));
						temp->id=id++;
//						printf("%13d born\t",temp->id);
                        temp->d='<';
                        temp->y=curr->y;
                        temp->x=curr->x;
                        temp->n=curr;
                        temp->p=curr->p;
                        if (curr->p) curr->p->n=temp;
                        else beams=temp;
                        curr->p=temp;
                    }
//					curr=curr->n;
                }
            }
			else if (curr->d=='<'){
                curr->x--;
                if (curr->x<0 || map[curr->y][0][curr->x]=='<' || map[curr->y][0][curr->x]=='>'){
//					printf("%13d died\t",curr->id);
                    if (curr->p) curr->p->n=curr->n;
                    else  beams=curr->n;
					if (curr->n) curr->n->p=curr->p;
                    temp=curr;
                    curr=curr->n;
                    free(temp);
                }
                else{
                    c=map[curr->y][0][curr->x];
                    if (map[curr->y][1][curr->x]==0) {energized++;map[curr->y][1][curr->x]=1;}
                    if (c=='\\') curr->d='^';
                    else if (c=='/') curr->d='V';
                    else if (c=='.') map[curr->y][0][curr->x]=curr->d;
                    else if (c=='|'){
                        curr->d='^';
                        temp=(struct beam*)malloc(sizeof(struct beam));
						temp->id=id++;
//						printf("%13d born\t",temp->id);
                        temp->d='V';
                        temp->y=curr->y;
                        temp->x=curr->x;
                        temp->n=curr;
                        temp->p=curr->p;
                        if (curr->p) curr->p->n=temp;
                        else beams=temp;
                        curr->p=temp;
                    }
//					curr=curr->n;
                }
            }
			else if (curr->d=='>'){
                curr->x++;
                if (curr->x>=width || map[curr->y][0][curr->x]=='<' || map[curr->y][0][curr->x]=='>'){
//					printf("%13d died\t",curr->id);
                    if (curr->p) curr->p->n=curr->n;
                    else  beams=curr->n;
                    if (curr->n) curr->n->p=curr->p;
                    temp=curr;
                    curr=curr->n;
                    free(temp);
                }
                else{
                    c=map[curr->y][0][curr->x];
                    if (map[curr->y][1][curr->x]==0) {energized++;map[curr->y][1][curr->x]=1;}
                    if (c=='\\') curr->d='V';
                    else if (c=='/') curr->d='^';
                    else if (c=='.') map[curr->y][0][curr->x]=curr->d;
                    else if (c=='|'){
                        curr->d='^';
                        temp=(struct beam*)malloc(sizeof(struct beam));
						temp->id=id++;
//						printf("%13d born\t",temp->id);
                        temp->d='V';
                        temp->y=curr->y;
                        temp->x=curr->x;
                        temp->n=curr;
                        temp->p=curr->p;
                        if (curr->p) curr->p->n=temp;
                        else beams=temp;
                        curr->p=temp;
                    }
//					curr=curr->n; //commenting these out might have decreased the result by 15 and made it correct idk
                }
            }
		}
	}
	puts("");
	for(int i=0;i<height;i++) {printf("%s\t",map[i][0]);for(int j=0;j<width;j++) printf("%d",map[i][1][j]); puts("");}
	printf("Answer: %d\n",energized);
}
