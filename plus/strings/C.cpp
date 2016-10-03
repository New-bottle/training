#include<cstdio>
#include<set>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;

int n, m, k;
set<int>p[13];
set<int>::iterator it;

char s[N], t[N];
int solve(char *t) {
	int l = strlen(t);
	for(int i = 0; i < k; i ++) p[i].clear();
	for(int i = 0; i < l; i ++)
		p[t[i] - 'a'].insert(i);
	int now = -1, times = 1;
	for(int i = 1; i <= n; i ++) {
		int x = s[i] - 'a';
		it = p[x].upper_bound(now);
		if (it == p[x].end()) {
			times ++;
			now = *p[x].begin();
		} else {
			now = *it;
		}
	}
	return times;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", s + 1);
	int opt;
	for(int i = 1; i <= m; i ++) {
		scanf("%d", &opt);
		if (opt == 1) {
			char ch;
			int l, r;
			scanf("%d%d %c", &l, &r, &ch);
//			printf("ch = %c\n", ch);
			for(int j = l; j <= r; j ++)
				s[j] = ch;
		} else {
			scanf("%s", t);
			printf("%d\n", solve(t));
		}
	}
	return 0;
}
