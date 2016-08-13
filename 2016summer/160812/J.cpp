#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

const int N = 100010;
int ch[N][26], tot, n, m;
int st[N], ed[N], v[N], num, nxt[N], lst[N], a[N];
char s[N];

void Insert(char *s, int w) {
	int x = 1, y, l = strlen(s);
	st[w] = num + 1;
	for(int i = 0; i < l; i ++) {
		y = s[i] - 'a';
		if (!ch[x][y]) ch[x][y] = ++ tot;
		x = ch[x][y];
		v[++ num] = x;
	}
	ed[w] = num;
}

struct node{
	int cnt, l, r;
}t[N * 30];
int rt[N], cnt;
#define mid ((l + r) >> 1)
void update(int &o, int l, int r, int pos){
	t[++ cnt] = t[o], o = cnt, ++ t[o].cnt;
	if (l == r) return;
	if (pos <= mid) update(t[o].l, l, mid, pos);
	else update(t[o].r, mid + 1, r, pos);
#ifdef debug
	printf("update %d %d %d %d %d\n", o, l, r, pos, t[o].cnt);
#endif
}

int query(int o, int l, int r, int ql, int qr){
//	printf("query %d %d %d %d %d %d\n", o, l, r, ql, qr, t[o].cnt);
	if (!o) return 0;
	if (ql <= l && qr >= r) return t[o].cnt;
	else{
		int ans = 0;
		if (ql <= mid) ans += query(t[o].l, l, mid, ql, qr);
		if (qr >  mid) ans += query(t[o].r, mid + 1, r, ql, qr);
		return ans;
	}
}
bool cmp(int x, int y){
	return nxt[x] > nxt[y];
}
void build(){
	memset(lst, 0, sizeof lst);
	memset(nxt, 0, sizeof nxt);
	for(int i = num; i; i --) {
		nxt[i] = lst[v[i]] ? lst[v[i]] : num + 1;
		lst[v[i]] = i;
	}
	for(int i = 1; i <= num; i ++) a[i] = i;
	sort(a + 1, a + num + 1, cmp);
	memset(t, 0, sizeof t[0] * cnt); cnt = 0;
	memset(rt, 0, sizeof rt);
#ifdef debug
	for(int i = 1; i <= num; i ++) printf("%d ", v[i]); puts("");
	for(int i = 1; i <= num; i ++) printf("%d ", nxt[i]); puts("");
	for(int i = 1; i <= num; i ++) printf("%d ", nxt[a[i]]); puts("");
#endif
//	for(int i = num; i; i --) rt[i] = rt[i + 1];
	int j = 1;
	for(int i = num + 1; i; i --) {
		rt[i] = rt[i + 1];
		while(nxt[a[j]] == i && j <= num) {
			update(rt[i], 1, num, a[j]);
			j ++;
		}
	}
	/*
	for(int i = 1; i <= num; i ++) {
		if (nxt[a[i]] != nxt[a[i - 1]])
			rt[nxt[a[i]]] = rt[nxt[a[i - 1]]];
		update(rt[nxt[a[i]]], 1, num, v[a[i]]);
	}
	*/
}

int getans(int l, int r) {
	l = st[l]; r = ed[r];
//	printf("getans %d %d num = %d\n", l, r, num);
	return query(rt[r + 1], 1, num, l, r);
}
int main(){
	while(scanf("%d", &n) == 1){
		tot = 1;
		num = 0;
		memset(ch, 0, sizeof ch);
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s);
			Insert(s, i);
		}
		build();
		scanf("%d", &m);
		int ans = 0, l, r, x, y;
		for(int i = 1; i <= m; i ++) {
			scanf("%d%d", &x, &y);
			l = min((ans + x) % n + 1, (ans + y) % n + 1);
			r = max((ans + x) % n + 1, (ans + y) % n + 1);
			ans = getans(l, r);
			printf("%d\n", ans);
		}
	}
	return 0;
}
