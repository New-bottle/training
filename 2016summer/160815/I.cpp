#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

struct ques{
	int l, r, pos1, pos2;
}q[N];
vector<int>p[N];
int ch[N][26], fail[N], len[N], tot, n, m, dfs_clock;
char s[N], t[30];

void ready(){
	memset(head, 0, sizeof head); cnt = 0;
	for(int i = 0; i <= tot; i ++) p[i].clear();
	memset(ch, 0, sizeof ch); tot = 0;
	len[0] = 0; len[1] = -1;
	fail[0] = 1; fail[1] = 0;
	dfs_clock = 0;
}
void Insert(char *s){
	int now = 1, l = strlen(s), x, y, tmp;
	for(int i = 0; i < l; i ++) {
		x = s[i] - 'a';
		while(s[i] != s[i - len[now] - 1]) now = fail[now];
		if (!ch[now][x]) {
			ch[now][x] = ++ tot;
			len[tot] = len[now] + 2;
		}
		y = ch[now][x];
		tmp = fail[now];
		if (tmp == -1) fail[y] = 0;
		else {
			while(s[i] != s[i - len[tmp] - 1]) tmp = fail[tmp];
			fail[y] = ch[tmp][x];
		}
		add(fail[y], y);
		now = y;
		p[now].push_back(i + 1);
	}
}
void find(char *s, int num){
	int now = 1, l = strlen(s), x;
	bool flag = 1;
	for(int i = 0; i < l; i ++) {
		x = s[i] - 'a';
		if (ch[now][x]) x = ch[now][x];
		else {
			flag = 0;
			break;
		}
	}
	q[num].pos1 = flag ? x : 0;
	now = 0; flag = 1;
	for(int i = 0; i < l; i ++) {
		x = s[i] - 'a';
		if (ch[now][x]) x = ch[now][x];
		else {
			flag = 0;
			break;
		}
	}
	q[num].pos2 = flag ? x : 0;
}

int st[N], ed[N], v[N];
bool vis[N];
void dfs(int x){
	st[x] = dfs_clock + 1;
	vis[x] = 1;
	for(int i = 0; i < p[x].size(); i ++)
		v[++ dfs_clock] = p[x][i];
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			dfs(to[i]);
		}
	ed[x] = dfs_clock;
}
int main(){
	while(scanf("%s", s) != EOF) {
		ready();
		Insert(s);
		for(int i = 1; i <= tot; i ++)
			if (!vis[i]) dfs(i);
		scanf("%d", &m);
		for(int i = 1; i <= m; i ++) {
			scanf("%d%d%s", &q[i].l, &q[i].r, t);
			find(t, i);
			printf("%d %d\n", q[i].pos1, q[i].pos2);
		}
	}
	return 0;
}
