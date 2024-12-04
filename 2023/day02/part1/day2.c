#include <stdio.h>
int main(){
	FILE *f = fopen("day2.txt","r");
	char line[200],type=0;
	int total=0,game=0,num=0,r=12,g=13,b=14,pass;
	while (fscanf(f,"Game %d: ",&game)>0){
		pass=1;
		while (fscanf(f,"%d %c%*s ",&num,&type)>0){
			if (num>(type=='g'?g:(type>'g'?r:b))) {
				pass=0;
				fgets(line,200,f);
				break;
			}
		}
		if (pass){
			total+=game;
		}
	}
	printf("%d\n",total);
	return 0;
}
