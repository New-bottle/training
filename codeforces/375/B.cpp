#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

char s[1000];
bool isch(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", s);
	s[n] = '_';
	int nowlen = 0, maxlen = 0, num = 0;
	bool in = 0;
	for(int i = 0; i <= n; i ++) {
		if (isch(s[i])) nowlen ++;
		else {
			if (!in) maxlen = max(maxlen, nowlen);
			else num += (nowlen > 0);
			nowlen = 0;
		}
		if (s[i] == '(') in = 1;
		else if (s[i] == ')') in = 0;
	}
	printf("%d %d\n", maxlen, num);
	return 0;
}
