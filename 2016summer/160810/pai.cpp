#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
	int cs = 0;
	while(1){
		system("./Jgen");
		system("./J < J.in > J.out");
		system("./Jac");
		if (system("diff J.out J.ans > NULL")){
			puts("WA!!!!");
			system("gedit NULL");
			return 0;
		}
		printf("AC : %d\n", ++ cs);
	}

	return 0;
}
