#include <stdio.h>
#include <time.h>
int main(){
	clock_t start, end;
    double cpu_time_used=0;
	start=clock();
	FILE *file = fopen("day12.txt","r");
	char s[21],test[21],pass,skip;
	int b[10],bstarts[10],bi,tlen,slen,blen,bsum,t;
	long total=0;
	while (fscanf(file,"%s",s)>0){
		for (slen=0;s[slen];slen++);
		t=0;
		blen=0;
		bsum=0;
		fscanf(file," %d",&b[blen]);
        bsum+=b[blen++];
		while (fscanf(file,",%d",&b[blen])>0) bsum+=b[blen++];
		bstarts[(bi=0)]=0;
		tlen=bsum+blen-1;
//		printf("%s",s);for (int i=0;i<blen;i++) printf(" %d,", b[i]);puts(""); //test print
		if (slen==tlen) {total++;t++;}
		else while (1){
			pass=1;
			for (int i=bstarts[bi];i<bstarts[bi]+b[bi];i++) if (i>=slen || s[i]=='.') {pass=0;break;}
			if ((bstarts[bi]==0 || !(skip=s[bstarts[bi]-1]=='#')) && pass && (bstarts[bi]+b[bi]==slen || s[bstarts[bi]+b[bi]]!='#')){
				if (bi==blen-1) {
					for (int i=bstarts[bi]+b[bi];i<slen;i++) if (s[i]=='#') pass=0;
					if (pass) {total++;t++;}
//					for(int i=0;i<slen;i++)test[i]='.';test[slen]=0;for(int i=0;i<blen;i++)for(int j=bstarts[i];j<bstarts[i]+b[i];j++)test[j]='#';printf("%s\n",test);
					bstarts[bi]++; //^test print
				}
				else {
					bstarts[bi+1]=bstarts[bi]+b[bi]+1;
					tlen-=1+b[bi++];
				}
			}
			else bstarts[bi]++;
			if (bi==blen || bstarts[bi]+tlen>slen || skip){
				skip=0;
				if (bi==0) break;
				bstarts[--bi]++;
				tlen+=1+b[bi];
			}
		}// printf("%d\n",t); //test print
	}
	printf("Answer: %ld\n",total);
	end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lfs\n",cpu_time_used);
	return 0;
}
