#include <stdio.h>
#include <stdlib.h>
typedef struct lens{
	int focus;
	char label[10];
	struct lens *left,*right;
} lens;
char match(char s1[10], char s2[10]){
	char i;
	for (i=0;s1[i] && s2[i];i++) if (s1[i]!=s2[i]) {break;}
	return s1[i]==0 && s2[i]==0;
}
int hash(char label[10]){
	int h=0;
	for (int i=0;label[i];i++) h=((h+label[i])*17)%256;
	return h;
}
void insert(lens *boxes[256],char label[10],int focus){
    int box=hash(label);
	lens *curr;
	if ((curr=boxes[box])){
		while(!match(curr->label,label) && curr->right) curr=curr->right;
		if (match(curr->label,label)) {curr->focus=focus;return;}
	}
	lens *new=(struct lens*)malloc(sizeof(struct lens));
	new->focus=focus;
	for (int i=0;i<10;i++) new->label[i]=0;
	for (int i=0;label[i];i++) new->label[i]=label[i];
	new->right=NULL;
	if (curr){
		curr->right=new;
		new->left=curr;
	}
	else {
		new->left=NULL;
		boxes[box]=new;
	}
}
void rm(lens *boxes[256],char label[10]){
	int box=hash(label);
    lens *curr;
    if ((curr=boxes[box])){
		while(!match(curr->label,label) && curr->right) curr=curr->right;
        if (match(curr->label,label)) {
			if (curr->left) curr->left->right=curr->right;
			if (curr->right) curr->right->left=curr->left;
			if (boxes[box]==curr) boxes[box]=curr->right;
			free(curr);
		}
	}
}
int main(){
	FILE *f=fopen("day15.txt","r");
	char label[10],op;
	int sum=0,focus;
	lens *boxes[256],*curr;
	for (int i=0;i<256;i++) boxes[i]=NULL;
	while(fscanf(f,"%[a-z]%1[=-]",label,&op)>0){
		if (op=='=') {
			fscanf(f,"%d,",&focus);
			insert(boxes,label,focus);
		}
		else{
			fscanf(f,",");
			rm(boxes,label);
		}
	}
	for(int i=0;i<256;i++) if ((curr=boxes[i])){
		for(int j=1; curr;j++){
			sum+=(i+1)*j*curr->focus;
			curr=curr->right;
		}
	}
	printf("Answer %d\n",sum);
	return 0;
}
