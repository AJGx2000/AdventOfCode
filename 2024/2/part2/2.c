#include <stdio.h>
#define SIZE 100 

int main(){
	FILE *fp = fopen("2test.txt","r");
	int last, curr, i,j,count=0;
	char line[SIZE],negative,temp;
	while(fgets(line,SIZE,fp)){
		i=0;
		sscanf(line,"%d %d%n",&curr,&last,&j);
		i+=j;
		printf("\n%s\n%d %d ",line,curr,last);
		negative = (curr = last-curr) >> 31;
		temp = !(curr && curr >= -3 && curr <=3);
	       	while(sscanf(line+i," %d%n",&curr,&j)>-1){
			i+=j;
			printf("%d ", curr);
			last=curr-last;
			if (!(last && (negative == last>>31) && last<=3 && last>=-3)) if(temp++) break;
			last=curr;
		}
		printf("%s - %d\n", (!temp)?"passed":"failed",temp);
		if(!temp) count+=1;
		//else printf("failed\n");
	}
	printf("%d\n",count);
	return 0;
}
