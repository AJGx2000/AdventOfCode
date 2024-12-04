#include <stdio.h>
#include <time.h>
int main(){
	clock_t start, end;
    double cpu_time_used=0;
	start=clock();
	FILE *file = fopen("day12.txt","r");
	int sconst=21,bconst=10,mconst=sconst*bconst,b[bconst],bstarts[bconst],mi,bi,tlen,slen,blen,bsum,t;
	long total=0, memo[mconst];
	char s[sconst],test[sconst],pass,skip;
	while (fscanf(file,"%s",s)>0){
		t=0;
		for (int i=0;i<mconst;i++) memo[i]=-1;
		for (slen=0;s[slen];slen++);
		blen=0;
		bsum=0;
		fscanf(file," %d",&b[blen]);
        bsum+=b[blen++];
		while (fscanf(file,",%d",&b[blen])>0) bsum+=b[blen++];
		bstarts[(bi=0)]=0;
		tlen=bsum+blen-1;
//		printf("%s",s);for (int i=0;i<blen;i++) printf(" %d,", b[i]);puts(""); //test print
		if (slen==tlen) total++;
		else while (1){
//			puts("");
//			for (int i=0;i<=bi;i++) printf("%d, ",bstarts[i]);
//			puts("");
//			puts("step 1");
			mi=bi*sconst+bstarts[bi];
//			printf("mi=%d*%d+%d=%d\n",bi,bconst,bstarts[bi],mi);
			if (bi<blen-1 && memo[mi]>-1) {
//				printf("%s\n",s);for(int i=0;i<slen;i++)test[i]='.';test[slen]=0;for(int i=0;i<blen;i++)for(int j=bstarts[i];j<bstarts[i]+b[i];j++)test[j]='#';printf("%s\n",test);
//				printf("Memo[%d]: %ld\n",mi,memo[mi]);
                total+=memo[mi];
				t+=memo[mi];
				if (memo[mi])for (int i=0; i<bi; i++) {memo[i*sconst+bstarts[i]]+=memo[mi];}//printf("memo[%d] +%ld\n",i*sconst+bstarts[i],memo[mi]);}
				bstarts[bi]++;
				if (bstarts[bi]+tlen>slen || s[bstarts[bi]-1]=='#'){
//					puts("step 2");
					bstarts[bi]--;
					bstarts[--bi]++;
                    tlen+=1+b[bi];
				}
                //bstarts[--bi]++;
                //tlen+=1+b[bi];
            }
			else{
//				puts("step 3");
				if (memo[mi]==-1) memo[mi]=0;
				pass=1;
				for (int i=bstarts[bi];i<bstarts[bi]+b[bi];i++) if (i>=slen || s[i]=='.') {pass=0;break;}
				if ((bstarts[bi]==0 || !(skip=s[bstarts[bi]-1]=='#')) && pass && (bstarts[bi]+b[bi]==slen || s[bstarts[bi]+b[bi]]!='#')){
//					puts("step 4");
					if (bi==blen-1) {
//						puts("step 5");
						for (int i=bstarts[bi]+b[bi];i<slen;i++) if (s[i]=='#') pass=0;
						if (pass) {
//							puts("step 6");
							total++;
							t++;
//							printf("+1\n");
							for (int i=0; i<=bi; i++) {memo[i*sconst+bstarts[i]]++;}//printf("memo[%d] +1\n",i*sconst+bstarts[i]);}
						}
//						printf("%s\n",s);for(int i=0;i<slen;i++)test[i]='.';test[slen]=0;for(int i=0;i<blen;i++)for(int j=bstarts[i];j<bstarts[i]+b[i];j++)test[j]='#';printf("%s\n",test);
						bstarts[bi]++; //^test print
					}
					else {
//						puts("step 7");
						bstarts[bi+1]=bstarts[bi]+b[bi]+1;
						tlen-=1+b[bi++];
					}
				}
				else {bstarts[bi]++;/*puts("step 8");*/}
				if (bi==blen || bstarts[bi]+tlen>slen || skip){
//					puts("step 9");
					skip=0;
					if (bi==0) break;
					bstarts[bi]--;
					bstarts[--bi]++;
					tlen+=1+b[bi];
				}
			}
		} //printf("%d\n",t); //test print
//		for (int i=0;i<blen;i++) {
//			mi=i*bconst;
//			for (int j=0;j<slen;j++) printf("%2ld, ",memo[mi+j]);
//			puts("");
//		}
	}
	printf("Answer: %ld\n",total);
	end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %lfs\n",cpu_time_used);
	return 0;
}
