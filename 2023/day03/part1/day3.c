#include <stdio.h>
int inRadius(int y,int x,int i,int j,int len){
	return y+i>-1 && y+i<140 && x+j>-1 && x+j<140 && !(i==0 && j>-1 &&j<len);
}
int isNum(char c) {
	return c>='0' && c <='9';
}
int evaluate(char mat[140][140], int y, int x){
	int num=0,len=0;
	while (x+len<140 && isNum(mat[y][x+len])){
		num*=10;
		num+=mat[y][x+len]-'0';
		len+=1;
	}
	for (int i=-1;i<2;i++) for (int j=-1;j<len+1;j++) if (inRadius(y,x,i,j,len) && !isNum(mat[y+i][x+j]) && mat[y+i][x+j]!='.') return num;
	return 0;
}
int main(){
	FILE *f=fopen("input.txt","r");
	int total=0;
	char mat[140][140], buff[142];
	for (int i=0;i<140;i++){
		fgets(buff,142,f);
		for (int j=0;j<140;j++) {
			mat[i][j]=buff[j];
		}
	}
	for (int i=0;i<140;i++) for (int j=0;j<140;j++) if (isNum(mat[i][j]) && !(j>0 && isNum(mat[i][j-1]))) total+=evaluate(mat,i,j);
	printf("%d\n",total);
	return 0;
}
