#include <stdio.h>
#include <stdlib.h>
typedef struct lens{
	int focus;
	char label[10];
	struct lens *left;
	struct lens *right;
} lens;
char match(char s1[10], char s2[10]){
	char m=1,i;
	for (i=0;s1[i] && s2[i];i++) if (s1[i]!=s2[i]) {m=0;break;}
	return m && s1[i]==0 && s2[i]==0;
}
int hash(char label[10]){
	int h=0;
	for (int i=0;label[i];i++) h=((h+label[i])*17)%256;
	return h;
}
int insert(lens *boxes[256],char label[10],int focus){
    int box=hash(label);
	lens *curr;
	if ((curr=boxes[box])){
		while(!match(curr->label,label) && curr->right) curr=curr->right;
		if (match(curr->label,label)) {curr->focus=focus;return box;}
	}
	lens *new=(struct lens*)malloc(sizeof(struct lens));
	new->focus=focus;
	for (int i=0;i<10;i++) new->label[i]=0;
	for (int i=0;label[i];i++) new->label[i]=label[i];
	new->right=NULL;
	if (curr){
//		printf("adding to end of box %d; this should be 0: %p\n",box,curr->right);
		curr->right=new;
		new->left=curr;
	}
	else {
//		printf("first in box %d; this should be 0: %p\n",box,boxes[box]);
		new->left=NULL;
		boxes[box]=new;
	}
	return box;
}
int rm(lens *boxes[256],char label[10]){
	int box=hash(label);
    lens *curr;
    if ((curr=boxes[box])){
		while(!match(curr->label,label) && curr->right) curr=curr->right;
        if (match(curr->label,label)) {
			if (curr->left) curr->left->right=curr->right;
			if (curr->right) curr->right->left=curr->left;
			if (boxes[box]==curr) boxes[box]=curr->right;
			free(curr);
			return box;
		}
	}
	return -box;
}
int main(){
	FILE *f=fopen("day15.txt","r");
	char label[10],op;
	int sum=0,focus,box;
	lens *boxes[256],*curr;
	for (int i=0;i<256;i++) boxes[i]=NULL;
	while(fscanf(f,"%[a-z]%1[=-]",label,&op)>0){
		box=hash(label);
		if (op=='=') {
			fscanf(f,"%d,",&focus);
//			printf("Box %d: ",box);	if ((curr=boxes[box])) for(int j=1; curr;j++) {printf("%d.[%s %d] ",j,curr->label,curr->focus);curr=curr->right;}puts("");
//			printf("Adding %s=%d to box %d\n",label,focus,insert(boxes,label,focus));
//          printf("Box %d: ",box);if ((curr=boxes[box])) for(int j=1; curr;j++) {printf("%d.[%s %d] ",j,curr->label,curr->focus);curr=curr->right;}puts("\n");
		insert(boxes,label,focus);
		}
		else{
			fscanf(f,",");
//			printf("Box %d: ",box);	if ((curr=boxes[box])) for(int j=1; curr;j++) {printf("%d.[%s %d] ",j,curr->label,curr->focus);curr=curr->right;}puts("");
//			printf("Removing %s- from box %d\n",label,rm(boxes,label));
//			printf("Box %d: ",box); if ((curr=boxes[box])) for(int j=1; curr;j++) {printf("%d.[%s %d] ",j,curr->label,curr->focus);curr=curr->right;}puts("\n");
		rm(boxes,label);
		}
	}
	/*
	for(int i=0;i<256;i++) if ((curr=boxes[i])){
		printf("Box %d: ",i);
		while (curr) {
			printf("[%s %d] ",curr->label,curr->focus);
			curr=curr->right;
		}
		puts("");
	}
	*/
	for(int i=0;i<256;i++) if ((curr=boxes[i])){
//		printf("Box %d (%d): ",i,i+1);
		for(int j=1; curr;j++){
//			printf("%d.[%s %d] ",j,curr->label,curr->focus);
			sum+=(i+1)*j*curr->focus;
			curr=curr->right;
		}
//		printf("\n\t\t\t\t\t\t\t%d\n",sum);
	}
	printf("Answer %d\n",sum);
	return 0;
}
