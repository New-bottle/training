#include<cstdio>
#include<cstdlib>

int main(){
	int cs = 0;
	while(1){
		system("gen");
		system("std < B.in > B.ans");
		system("B < B.in > B.out");
		if (system("fc B.out B.ans > null")){
			puts("!!!");
			break;
		}
		printf("AC : %d\n",++ cs);
	}
	return 0;
}
