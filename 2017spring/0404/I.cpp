#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 500010;

struct node{
	int ch;
	int n;
	bool operator < (const node &b) const {
		return n < b.n || (n == b.n && ch < b.ch);
	}
}a[26];
int cnt[26];
char s[N];

int main()
{
	int T, cs = 0;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ++cs);
		memset(cnt, 0, sizeof cnt);
		while (gets(s)) {
			if (s[0] == '*') break;
			int l = (int)strlen(s);
			for (int i = 0; i < l; ++i)
				if (s[i] >= 'a' && s[i] <= 'z') ++cnt[s[i] - 'a'];
				else if (s[i] >= 'A' && s[i] <= 'Z') ++cnt[s[i] - 'A'];
		}
		for (int i = 0; i < 26; ++i) a[i] = (node){i, cnt[i]};
		sort(a, a + 26);
//		for (int i = 0; i < 26; ++i) printf("%d %d\n", a[i].ch, a[i].n);
		int sm = 0;
		for (int i = 25; i > 20; --i)
			if (a[i].n) sm += a[i].ch;
		if (sm > 62) puts("Effective");
		else puts("Ineffective");
	}
	return 0;
}
