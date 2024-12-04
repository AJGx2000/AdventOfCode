#include <stdio.h>
int isNum(char c) {
    return c>='0' && c <='9';
}
int isValid(int y,int x){
	return y>-1 && y<140 && x>-1 && x<140;
}
int findInt(char mat[140][140], int y,int x){
	int num=0;
	while (x>0 && isNum(mat[y][x-1])) x--;
	while (x<140 && isNum(mat[y][x])){
		num*=10; 
		num+=mat[y][x++]-'0';
	}
	return num;
}
int evaluate(char mat[140][140], int y, int x){
	int product=1,count=0;
	for (int i=-1;i<2;i++) for (int j=-1;j<2;j++) if (!(j==0 && i==0) && isValid(y+i,x+j) && isNum(mat[y+i][x+j]) && (j==-1 || x+j==0 ||(x+j>0 && !isNum(mat[y+i][x+j-1])))){
		product*=findInt(mat,y+i,x+j);
		count++;
	}
	return count>1?product:0;
}
int main(){
	FILE *f=fopen("day3.txt","r");
	int total=0;
	char mat[140][140], buff[142];
	for (int i=0;i<140;i++){
		fgets(buff,142,f);
		for (int j=0;j<140;j++) {
			mat[i][j]=buff[j];
		}
	}
	for (int i=0;i<140;i++) for (int j=0;j<140;j++) if (mat[i][j]=='*') total+=evaluate(mat,i,j);
	printf("%d\n",total);
	return 0;
}
