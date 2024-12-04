#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct node{
	char name[4];
	int alpha;
	char lr[2][4];
	struct node *L;
	struct node *R;
	struct node *ML;
    struct node *MR;
	int mapped;
} node;
node *dict;
int score(char n[4]){
	return (n[0]-'A')*676+(n[1]-'A')*26+n[2]-'A';
}
void print(node *n){
	printf("\n\tName: %s\n\tAddress: %p\n\tAlpha: %d\n\t%s\t%s\n\t%p\t%p\n\tMapped = %d\n\t%p\t%p\n",n->name,n,n->alpha,n->lr[0],n->lr[1],n->L,n->R,n->mapped,n->ML,n->MR);
}
node *newNode(char n[4],char lr[2][4]){
	node *node=(struct node *)malloc(sizeof(struct node));
	for (int i=0;i<4;i++) node->name[i]=n[i];
	node->alpha=score(n);
	node->L=NULL;
	node->R=NULL;
	for (int i=0;i<2;i++) for (int j=0;j<4;j++) node->lr[i][j]=lr[i][j];
	node->mapped=0;
	return node;
}
void insert(node *n){
	node *curr=dict;
	int i=0;
//	puts("*****START*****");
//	print(curr);
	while ( (n->alpha > curr->alpha && curr->R) || (n->alpha < curr->alpha && curr->L)){
//		puts("*****STEP*****");
		if (n->alpha > curr->alpha) /*{puts("r");*/curr=curr->R; else /*{puts("l");*/curr=curr->L;
//		print(curr);
	}
	if (n->alpha > curr->alpha) /*{puts("***INSERTED RIGHT***");*/curr->R=n; else /*{puts("***INSERTED LEFT***");*/curr->L=n;
	return;
}
node *search(char n[4]){
	int key=score(n);
	node *curr=dict;
	while (curr && curr->alpha!=key){
		if (key>curr->alpha) curr=curr->R;
		else curr=curr->L;
	}
	if (key==curr->alpha) return curr;
	else return NULL;
}
void completeMap(node *n){
	if (!n || n->mapped) return;
	n->ML=search(n->lr[0]);
	n->MR=search(n->lr[1]);
	n->mapped=1;
	completeMap(n->ML);
	completeMap(n->MR);
	return;
}
int walk(node *m,char d[310]){
	int steps=0,end=score("ZZZ\0");
	while (m->alpha!=end) if (d[steps++%307]=='L') m=m->ML; else m=m->MR;
	return steps;
}
int main(){
	FILE *f=fopen("day8.txt","r");
	char directions[310];
	node  *map, *n;
	char name[4],lr[2][4];
	fscanf(f,"%s",directions);

	fscanf(f," %3s = ( %3s, %3s )",name,lr[0],lr[1]); 
	dict=newNode(name,lr);
	while (fscanf(f," %3s = ( %3s, %3s )",name,lr[0],lr[1])>0) {
//		printf("**********INSERTING %s***********\n",name);
		insert(newNode(name,lr));
	}
	map =search("AAA\0");
	//print(map);
	completeMap(map);
	printf("Answer: %d\n",walk(map,directions));
	return 0;
}
