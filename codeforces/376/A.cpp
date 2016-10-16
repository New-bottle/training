#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, m;
char s[N];

int main() {
	scanf("%s", s);
	int l = strlen(s), now = 0, ans = 0;
	for(int i = 0; i < l; i ++) {
		ans += min(abs(s[i] - 'a' - now), 26 - abs(s[i] - 'a' - now));
		now = s[i] - 'a';
//		printf("ans = %d\n", ans);
	}
	printf("%d\n", ans);
	return 0;
}
