#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int N = 200010;

int k, a[N], n;
char s[N];

struct node
{
	int num[26];
	node(){memset(num, 0, sizeof num);}
	int & operator [] (int x) {return num[x];}
//	const int& operator [] (int x} const {return num[x];}
	friend node operator - (const node &a, const node &b) {
		node c;
		for (int i = 0; i < 26; ++i)
			c.num[i] = a.num[i] - b.num[i];
		return c;
	}
	friend bool operator < (const node &a, const node &b) {
		int v1 = 0, v2 = 0;
		for (int i = 0; i < 26; ++i) {
			v1 += a.num[i] > 0;
			v2 += b.num[i] > 0;
		}
		return v1 < v2;
	}
}have[N];

inline int id(char c) {return c - 'a';}

int t[N << 2];
#define mid (l + r >> 1)
#define L (o << 1)
#define R (o << 1 | 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void update(int o, int l, int r, int pos, int x) 
{
	if (l == r) t[o] = x;
	else {
		if (pos <= mid) update(lch, pos, x);
		else update(rch, pos, x);
		t[o] = min(t[L], t[R]);
	}
}

int query(int o, int l, int r, int ql, int qr) 
{
	if (ql <= l && qr >= r) return t[o];
	else {
		int ans = 1e9;
		if (ql <= mid) ans = min(ans, query(lch, ql, qr));
		if (qr >  mid) ans = min(ans, query(rch, ql, qr));
		return ans;
	}
}
#undef L
#undef R
#undef mid

int ans[N];
int main()
{
	scanf("%d", &k);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		have[i] = have[i - 1];
		++have[i][s[i] - 'a'];
	}
	for (int i = 1; i <= n; ++i) {
		int L = 0, R = i - 1, num = 0;
		for (int j = 0; j < 26; ++j) num += have[i].num[j] > 0;
		if (num < k) {
			ans[i] = -1;
			update(1, 0, n, i, INF);
		} else {
			printf("num = %d\n", num);
			node tmp;
			for (int j = 0; j < num - k; ++j) tmp.num[j] = 1;
	//		num - k;
			int l = lower_bound(have + 1, have + i, tmp) - have - 1,
				r = upper_bound(have + 1, have + i, tmp) - have - 1;
			printf("l = %d r = %d\n", l, r);
			if (l == i) {
				ans[i] = -1;
				update(1, 0, n, i, INF);
			} else {
				ans[i] = query(1, 0, n, l, r) + 1;
				update(1, 0, n, i, ans[i]);
			}
		}
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	return 0;
}
