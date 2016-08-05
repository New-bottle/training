#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
	int cs = 0;
	while(1){
		system("./gen > D.in");
		system("time ./D < D.in > D.out");
		system("time ./Dstd < D.in > D.ans");
		if (system("diff D.out D.ans > NULL")){
			puts("WA!!!");
			break;
		}
		printf("AC : %d\n", ++ cs);
		if (cs == 1000) break;
	}
	return 0;
}
