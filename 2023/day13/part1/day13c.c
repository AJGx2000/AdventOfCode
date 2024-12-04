#include <stdio.h>
int main(){
	FILE *f=fopen("day13.txt","r");
	char mat[20][20],width,height,b; //break
	int above=0,left=0;
	do {
		b=1;
		height=-1;
		while (fscanf(f,"%[.#]%*1[\n]",mat[++height])>0);
		for (width=0;mat[0][width];width++);
//		for (int i=0;i<height;i++) printf("%s\n",mat[i]); printf("%dx%d\n\n",height,width);
		for (int i=0;i<height-1 && b;i++){
			b=0;
			for (int j=0;!b && i+1+j<height && i-j>=0;j++) for (int k=0;!b && k<width;k++) if (mat[i-j][k]!=mat[i+1+j][k]) {b=1; 
//				printf("Failure for mirror between rows %d and %d: the %d%s character did not match in row %d and row %d\n",i,i+1,k,k==1?"st":k==2?"nd":k==3?"rd":"th",i-j,i+1+j);
			}
//			printf("b: %d\n",b);
			if (!b) above+=i+1;
//			if (!b) printf( "Mirror between rows %d and %d\n",i,i+1);
		}
		for (int i=0;i<width-1 && b;i++){
            b=0;
            for (int j=0;!b && i+1+j<width && i-j>=0;j++) for (int k=0;!b && k<height;k++) if (mat[k][i-j]!=mat[k][i+1+j]) {b=1;
//				printf("Failure for mirror between columnss %d and %d: the %d%s character did not match in column %d and column %d\n",i,i+1,k,k==1?"st":k==2?"nd":k==3?"rd":"th",i-j,i+1+j);
			}
//			printf("i: %d\tb: %d\n",i,b);
            if (!b) left+=i+1;
//			if (!b) printf( "Mirror between columns %d and %d\n",i,i+1);
        }
	}
	while (fgets(mat[0],2,f));
	printf("Answer: %d\n%d %D\n",above*100+left,above,left);
	return 0;
}
