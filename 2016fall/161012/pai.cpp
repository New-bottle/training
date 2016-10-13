#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
	int cs = 0;
	while(1) {
		system("./gen > J.in");
		system("./J < J.in > J.out");
		system("./Jstd < J.in > J.ans");
		if (system("diff J.out J.ans > NULL")) {
			puts("WA!!!");
			system("vimdiff J.out J.ans");
			break;
		}
		printf("AC : %d\n", ++ cs);
		if (cs == 1000) break;
	}
	return 0;
}
