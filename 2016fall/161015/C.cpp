#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

char s[N];
int n;

int main(){
	scanf("%s", s);
	n = strlen(s);
	int st = -1;
	for(int i = 0; i < n; i ++) {
		if (s[i] != 'a') {
			s[i] = s[i] - 1;
			if (st == -1) st = i;
		} else if (st != -1) break;
	}
	if (st == -1) {
		s[n - 1] = 'z';
	}
	puts(s);
	return 0;
}
