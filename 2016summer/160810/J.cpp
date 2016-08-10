#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define debug

const int N = 100010;
char s[4][N], ans[N];
int n, m, pos[N], num[4], d[4], all;
bool vis[N];

bool check() {
	bool yes = 0;
	for(int i = 1; i <= 3; i ++){
		int t1 = i % 3 + 1, t2 = i % 3 + 2;
		if (t2 == 4) t2 = 1;
		if (d[i] + min(d[t1] - num[t1], d[t2] - num[t2]) + all >= num[i])
			yes = 1;
	}
	return yes;
}
int main(){
	freopen("J.out","w",stdout);
	while(scanf("%d%d", &n, &m) == 2 && n){
		memset(vis, 0, sizeof vis);
		scanf("%s%s%s", s[1] + 1, s[2] + 1, s[3] + 1);
		num[1] = num[2] = num[3] = 0;
		int tot = 0;
		all = 0;
		for(int i = 1; i <= n; i ++) s[0][i] = 'A';
		for(int i = 1; i <= n; i ++){
			if (s[1][i] != s[2][i] && s[2][i] != s[3][i] && s[1][i] != s[3][i]) all ++;
			else if (s[1][i] == s[2][i] && s[1][i] == s[3][i]) {}
			else if (s[1][i] == s[2][i]) num[3] ++;
			else if (s[1][i] == s[3][i]) num[2] ++;
			else if (s[2][i] == s[3][i]) num[1] ++;
		}
#ifdef debug
		for(int i = 1; i <= 3; i ++) printf("num[%d] = %d\n", i, num[i]);
		printf("all = %d\n", all);
#endif
		d[1] = d[2] = d[3] = m - all;
		int tmp = 1;
		while (tot < m * 3 && tmp <= n) {
			while(vis[tmp]) tmp ++;
			if (tmp <= n) pos[++ tot] = tmp ++;
		}
		bool yes = 0;
		for(int j = 1; j <= 3; j ++) if (check()) yes = 1;
		if (!yes){
			puts("-1");
			continue;
		}
		for(int x = 1; x <= n; x ++){
			if (s[1][x] == s[2][x] && s[1][x] == s[3][x]){
				all --;
				ans[x] = 'A';
				if (s[1][x] == 'A') continue;
				d[1] --; d[2] --; d[3] --;
				if (check()) continue;
				else {
					d[1] ++;
					d[2] ++;
					d[3] ++;
					ans[x] = s[1][x];
				}
				continue;
			}
			static char ch[5];
			for(int j = 0; j <= 3; j ++) ch[j] = s[j][x];
			sort(ch, ch + 4);
			bool yes = 0;
			num[1] -= s[2][x] == s[3][x];
			num[2] -= s[1][x] == s[3][x];
			num[3] -= s[1][x] == s[2][x];
			for(int j = 0; j <= 3; j ++) {
				ans[x] = ch[j];
				d[1] -= s[1][x] != ans[x];
				d[2] -= s[2][x] != ans[x];
				d[3] -= s[3][x] != ans[x];
				printf("j = %d | %d %d %d\n", j, d[1], d[2], d[3]);
				for(int k = 1; k <= 3; k ++) printf("num[%d] = %d ", k, num[k]); puts("");
				if (check()) break;
				d[1] += s[1][x] != ans[x];
				d[2] += s[2][x] != ans[x];
				d[3] += s[3][x] != ans[x];
			}
		}
		printf("%s\n", ans + 1);
		ans[0] = ans[1] = ans[2] = '\0';
	}
	return 0;
}
