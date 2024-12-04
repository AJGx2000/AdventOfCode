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
//	int mapped;
} node;
node *dict;
int score(char n[4]){
	return (n[0]-'A')*676+(n[1]-'A')*26+n[2]-'A';
}
void print(node *n){
	printf("\n\tName: %s\n\tAddress: %p\n\tAlpha: %d\n\t%s\t%s\n\t%p\t%p\n\t%p\t%p\n"/*\tMapped: %d"*/,n->name,n,n->alpha,n->lr[0],n->lr[1],n->L,n->R,n->ML,n->MR);/*n->mapped);*/
}
node *newNode(char n[4],char lr[2][4]){
	node *node=(struct node *)malloc(sizeof(struct node));
	for (int i=0;i<4;i++) node->name[i]=n[i];
	node->alpha=score(n);
	node->L=NULL;
	node->R=NULL;
	for (int i=0;i<2;i++) for (int j=0;j<4;j++) node->lr[i][j]=lr[i][j];
	//node->mapped=0;
	return node;
}
void insert(node *n){
	node *curr=dict;
	int i=n->alpha;
//	puts("*****START*****");
//	print(curr);
	while ( (i > curr->alpha && curr->R) || (i < curr->alpha && curr->L)){
//		puts("*****STEP*****");
		if (i > curr->alpha) /*{puts("r");*/curr=curr->R; else /*{puts("l");*/curr=curr->L;
//		print(curr);
	}
	if (i > curr->alpha) /*{puts("***INSERTED RIGHT***");*/curr->R=n; else /*{puts("***INSERTED LEFT***");*/curr->L=n;
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
	//if (!n /*|| n->mapped*/) return;
	n->ML=search(n->lr[0]);
	n->MR=search(n->lr[1]);
	//n->mapped=1;
	if (n->L) completeMap(n->L);
	if (n->R) completeMap(n->R);
	return;
}
void freeMap(node *n){
    //if (!n /*|| n->mapped*/) return;
    //n->ML=search(n->lr[0]);
    //n->MR=search(n->lr[1]);
    //n->mapped=1;
    if (n->L) freeMap(n->L);
    if (n->R) freeMap(n->R);
	free(n);
    return;
}
int walk(node *m,char d[310]){
	int steps=0;
	while (m->name[2]!='Z')  m=d[steps++%307]=='R'?m->MR:m->ML;
	return steps;
}
int gcd(int n, int m){
	int t;
	if (n<m) {
		t=n;
		n=m;
		m=t;
	}
	while (m) {
		n%=m;
	    t=n;
        n=m;
        m=t;
	}
	return n;
}
int main(){
	clock_t start, end;
    double cpu_time_used=0;
	int loops;
	puts("How many loops for average: ");
	scanf("%d",&loops);
	long answer;
    for (int j=0;j<loops;j++){
	start = clock();
	
	FILE *f=fopen("day8.txt","r");
	int len=6;
	char directions[310], starts[len][4];
	int index=0,g;
	long walks[len];
	node *maps[len];
	node *n;
	char name[4],lr[2][4];
	fscanf(f,"%s",directions);
	
//	for (int i=0;i<307;i++) directions[i]=directions[i]=='L'?0:1;

	fscanf(f," %3s = ( %3s, %3s )",name,lr[0],lr[1]); 
	dict=newNode(name,lr);
	while (fscanf(f," %3s = ( %3s, %3s )",name,lr[0],lr[1])>0) {
//		printf("**********INSERTING %s***********\n",name);
		if (name[2]=='A') {
			for (int i=0;i<4;i++) starts[index][i]=name[i];
			index++;
		}
		insert(newNode(name,lr));
	}
	index=0;
	for (int i=0;i<len;i++) maps[i]=search(starts[i]);
	completeMap(dict);
	for (int i=0;i<len;i++) walks[i]=walk(maps[i],directions);
//	for (int i=0;i<len;i++) printf("Map %s: %ld Steps\n",starts[i],walks[i]);
	g=gcd(walks[0],walks[1]);
	for (int i=2;i<len-1;i+=2) g=gcd(g,gcd(walks[i],walks[i+1]));
	if (len%1) g=gcd(g,walks[len-1]);
//	printf("GCD: %d\n",g);
	for (int i=1;i<len;i++) walks[i]/=g;
	//walks[0]*=g;/
	for (int i=1;i<len;i++) walks[0]*=walks[i];
	/*
	while (len>1) {
		for (int i=0;i<len-1;i+=2) walks[i/2]=(walks[i]*walks[i+1])/(gcd(walks[i],walks[i+1])*gcd(walks[i],walks[i+1]));
		if (len%1) walks[len/2]=walks[len-1];
		len=len/2+len%1;
	}*/
//	printf("Answer: %ld\n",walks[0]);

	end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	fclose(f);
	freeMap(dict);
	answer=walks[0];
	}
	printf("Answer: %ld\n",answer);
	printf("Average Time: %lfs\n",cpu_time_used/loops);
	return 0;
}
