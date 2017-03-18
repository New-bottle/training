#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200010;

char s[N];
int n;
bool check(int l, int r)
{
	int i = l, j = r;
	while(i < j)
	{
		if (s[i] != s[j]) return 0;
		++i; --j;
	}
	return 1;
}
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int pos = 0;
	for (int i = 1; i <= n; ++i)
		if (s[i] == s[n - i + 1]) continue;
		else {
			pos = i;
			break;
		}
	if (!pos) {
		puts("YES");
		printf("%d\n", (n + 1) / 2);
		return 0;
	}
	int ans = 0;
	if (check(pos + 1, n - pos + 1)) {
		ans = pos;
	} else if (check(pos, n - pos)) {
		ans = n - pos + 1;
	}
	if (ans) {
		puts("YES");
		printf("%d\n", ans);
	} else puts("NO");
	return 0;
}
/*
evertree
eertree
eertreve
   */
