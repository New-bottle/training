#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	char str[30];
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		scanf("%s", str);
		if(strstr(str, "GB")) printf("Case #%d: 6.87%%\n", i);
		else if(strstr(str, "TB")) printf("Case #%d: 9.05%%\n", i);
		else if(strstr(str, "PB")) printf("Case #%d: 11.18%%\n", i);
		else if(strstr(str, "EB")) printf("Case #%d: 13.26%%\n", i);
		else if(strstr(str, "ZB")) printf("Case #%d: 15.30%%\n", i);
		else if(strstr(str, "YB")) printf("Case #%d: 17.28%%\n", i);
		else if(strstr(str, "MB")) printf("Case #%d: 4.63%%\n", i);
		else if(strstr(str, "KB")) printf("Case #%d: 2.34%%\n", i);
		else printf("Case #%d: 0.00%%\n", i);
	}
}
