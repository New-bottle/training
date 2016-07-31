#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
	int cs = 0;
	while(1){
		system("./gen > G.in");
		system("./G < G.in > G.out");
		system("./Gstd < G.in > G.ans");
		if (system("diff G.out G.ans > NULL")){
			puts("WA!!!");
			break;
		}
		printf("AC : %d\n", ++ cs);
		if (cs == 1000) break;
	}
	return 0;
}
