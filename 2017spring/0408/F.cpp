#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 30100;

string ans[N];
char tmp[30], s1[20], s2[20];
int l1, l2, cnt;
void dfs (int x1, int x2)
{
	if (x1 == l1 && x2 == l2) {
		tmp[l1 + l2] = 0;
		ans[++cnt] = (tmp);
		return;
	}
	if (x1 < l1) {
		tmp[x1 + x2] = s1[x1];
		dfs(x1 + 1, x2);
	}
	if (x2 < l2) {
		tmp[x1 + x2] = s2[x2];
		dfs(x1, x2 + 1);
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		cin >> s1 >> s2;
		cnt = 0;
		l1 = strlen(s1); l2 = strlen(s2);
		dfs(0, 0);
		sort(ans + 1, ans + cnt + 1);
//		cout << "cnt = " << cnt << endl;
		cnt = unique(ans + 1, ans + cnt + 1) - ans - 1;
		for (int i = 1; i <= cnt; ++i)
			cout << ans[i] << '\n';
		cout << '\n';
	}
	return 0;
}
