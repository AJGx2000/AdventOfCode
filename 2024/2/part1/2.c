#include <stdio.h>
#define SIZE 100
#define signmask 

int main(){
	FILE *fp = fopen("2.txt","r");
	int last, curr, i,j,count=0;
	char line[SIZE],negative,temp;
	while(fgets(line,SIZE,fp)){
		i=0;
		sscanf(line,"%d %d%n",&curr,&last,&j);
		i+=j;
		//printf("\n%s\n%d %d ",line,curr,last);
		negative = (temp=last-curr) >> 31;
		if (temp && temp >= -3 && temp <=3){
			temp=1;
	       		while(sscanf(line+i," %d%n",&curr,&j)>-1){
				i+=j;
			//	printf("%d ", curr);
				last=curr-last;
				if (!(last && negative == last>>31 && last<=3 && last>=-3)) {
					temp=0;
					break;
				}
				last=curr;
			}
			//printf("%s\n", temp?"passed":"failed");
			count+=temp;
		}
		//else printf("failed\n");
	}
	printf("%d\n",count);
	return 0;
}
