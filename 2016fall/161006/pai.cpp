#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
	int cs = 0;
	while(cs ++ < 100) {
		system("./gen");
		system("./I < I.in > I.out");
		system("./Istd < I.in > I.ans");
		if (system("diff I.out I.ans > NULL")) {
			puts("WA!!!");
			system("vimdiff I.out I.ans");
			break;
		}
		printf("AC : %d\n", cs);
	}
	return 0;
}
