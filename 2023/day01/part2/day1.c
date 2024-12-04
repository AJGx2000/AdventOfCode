#include <stdio.h>
#include <string.h>
int check(char *s,int i){
	if (s[i]<':' && s[i]>'/'){
		return s[i];
	}
	else if (s[i]=='z') if (s[i+1]=='e') if (s[i+2]=='r') if (s[i+3]=='o') return '0';
	else if (s[i]=='o') if (s[i+1]=='n') if (s[i+2]=='e') return '1';
	else if (s[i]=='t'){
		if (s[i+1]=='w') if (s[i+2]=='o') return '2';
		else if (s[i+1]=='h') if (s[i+2]=='r') if (s[i+3]=='e') if (s[i+4]=='e') return '3';
	}
	else if (s[i]=='f'){
		if (s[i+1]=='o') if (s[i+2]=='u') if (s[i+3]=='r') return '4';
		else if (s[i+1]=='i') if (s[i+2]=='v') if (s[i+3]=='e') return '5';
	}
	else if (s[i]=='s'){
		if (s[i+1]=='i') if (s[i+2]=='x') return '6';
		else if (s[i+1]=='e') if (s[i+2]=='v') if (s[i+3]=='e') if (s[i+4]=='n') return '7';
	}
	else if (s[i]=='e') if (s[i+1]=='i') if (s[i+2]=='g') if (s[i+3]=='h') if (s[i+4]=='t') return '8';
	else if (s[i]=='n') if (s[i+1]=='i') if (s[i+2]=='n') if (s[i+3]=='e') return '9';
	return -1;
}

int main(){
	FILE *fp=fopen("day1.txt","r");
	char line[100];
	int first,last,num,total=0,base='0'*10+'0';
	while(fgets(line,100,fp)){
		first=last=0;
		for (int i=0;line[i];i++){
			if ((num=check(line,i))>-1){
				if (!first) first=num;
				last=num;
			}
		}
		total+=first*10+last-base;
	}
	printf("%d\n",total);
	return 0;
}
