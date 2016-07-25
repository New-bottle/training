#include<cstdio>
#include<cstdlib>

int main(){
	int cs = 0;
	while(1){
		system("gen");
		system("F < F.in > F.out");
		system("Fstd < F.in > F.ans");
		if (system("fc F.out F.ans > NULL")){
			puts("!!!");
			return 0;
		}
		printf("AC : %d\n", ++ cs);
	}
	return 0;
}
