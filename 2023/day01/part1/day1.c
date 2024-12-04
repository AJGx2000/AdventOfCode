#include <stdio.h>
int main(){
	FILE *fp=fopen("day1.txt","r");
	char line[100];
	int first,last,total=0,base='0'*10+'0';
	while(fgets(line,100,fp)){
		//printf("%s\n",line);
		first=last=0;
		for (int i=0;line[i];i++){
			if (line[i]<':' && line[i]>'/'){
				if (!first) first=line[i];
				last=line[i];
			}
		}
		total+=first*10+last-base;
	}
	printf("%d\n",total);
	return 0;
}
