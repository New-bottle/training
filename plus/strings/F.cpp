#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10000010;

char s[N], t[N];
int n, fail[N];

void init() {
	int l = strlen(t + 1);
	for(int i = 1; i <= l; i ++) {
		int j = fail[i];
		while(t[i + 1] != t[j + 1] && j) j = fail[j];
		if (t[i + 1] == t[j + 1]) fail[i + 1] = j + 1;
		else fail[i + 1] = 0;
	}
}
int main(){
	scanf("%d", &n);
	scanf("%s", t + 1);
	scanf("%s", s + 1);
	reverse(t + 1, t + strlen(t + 1) + 1);
	reverse(s + 1, s + strlen(s + 1) + 1);
	init();
	int mx = 0, l = strlen(s + 1), m = strlen(t + 1), j = 0;
	for(int i = 0; i <= l; i ++) {
		while(s[i + 1] != t[j + 1] && j) j = fail[j];
		if (s[i + 1] == t[j + 1]) j ++;
		mx = max(j, mx);
	}
	if (l + m - mx * 2 <= n) puts("Yes");
	else puts("No");
	return 0;
}
