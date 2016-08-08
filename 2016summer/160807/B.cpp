#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
//#define debug

typedef long long LL;
const int P = 1e9 + 7;
const int N = 200010;

int v[N * 2];
LL ans;
int n, m, h, w, num;
//set = -1 null
//set = 0 all = zero
//set = 1 all = one
struct node{
	int min, max, tag, sum;
}t[N << 2];
#define mid ((l + r) >> 1)
#define L (o << 1)
#define R (o << 1 | 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o, int l, int r){
	t[o].min = min(t[L].min, t[R].min);
	t[o].max = max(t[L].max, t[R].max);
	t[o].sum = t[L].sum + t[R].sum;
	if (t[o].min) t[o].sum = v[r] - v[l] + 1;
}

void change(int o, int l, int r, int val){
	t[o].tag += val;
	t[o].max += val;
	t[o].min += val;
	if (t[o].min) t[o].sum = v[r] - v[l] + 1;
	else if (t[o].max){
		change(lch, t[o].tag);
		change(rch, t[o].tag);
		t[o].tag = 0;
		Push_up(o, l, r);
	}else{
		t[o].sum = 0;
	}
}

void Push_down(int o, int l, int r){
	if (t[o].tag){
		change(lch, t[o].tag);
		change(rch, t[o].tag);
		t[o].tag = 0;
	}
}

void update(int o, int l, int r, int ql, int qr, int val){
	if (ql > qr) return;
	if (ql <= l && qr >= r) change(o, l, r, val);
	else{
		Push_down(o, l, r);
		if (ql <= mid) update(lch, ql, qr, val);
		if (qr >  mid) update(rch, ql, qr, val);
		Push_up(o, l, r);
	}
}

struct Rec{
	int x1, y1, x2, y2;
	void read(){
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	}
}rec[N], a[N];

struct Event{
	int l, r, y, rank;
}e[N];
bool operator < (const Event &a, const Event &b){
	return a.y < b.y || (a.y == b.y && a.rank < b.rank);
}

void solve(){
	num = 0;
	for(int i = 1; i <= n; i ++){
		a[i] = rec[i];
		a[i].x1 = max(1, a[i].x1 - m + 1);
		v[++ num] = a[i].x1;
		v[++ num] = a[i].x2;
	}
	a[++ n] = (Rec){max(1, w - m + 2), 1, w, h};
	v[++ num] = a[n].x1;
	v[++ num] = a[n].x2;

	sort(v + 1, v + num + 1);
	num = unique(v + 1, v + num + 1) - v - 1;
	for(int i = 1; i <= num; i ++) printf("%d ", v[i]); puts("");
	for(int i = 1; i <= n; i ++){
		a[i].x1 = lower_bound(v + 1, v + num + 1, a[i].x1) - v;
		a[i].x2 = lower_bound(v + 1, v + num + 1, a[i].x2) - v;
	}
	for(int i = 1; i <= n; i ++){
		e[i]     = (Event){a[i].x1, a[i].x2, a[i].y1, 1};
		e[n + i] = (Event){a[i].x1, a[i].x2, a[i].y2, 2};
	}
	sort(e + 1, e + n * 2 + 1);
	LL tmp = 0;
	e[n * 2 + 1].y = h;
	for(int i = 1; i <= n * 2; i ++){
		if (e[i].rank == 1)
			update(1, 1, num, e[i].l + 1, e[i].r, 1);
		if (e[i].rank == 2)
			update(1, 1, num, e[i].l + 1, e[i].r, -1);

//		if (e[i + 1].y != e[i].y || i == n * 2)
			tmp += (LL)t[1].sum * (e[i + 1].y - e[i].y + 1);
		printf("t[1].sum = %d\n", t[1].sum);


		printf("%d %d %d %d ", e[i].l, e[i].r, e[i].y, e[i].rank);
		printf("tmp = %d !!\n", tmp);
	}
	printf("tmp = %lld\n", tmp);
	ans += (LL)w * h - tmp;
	n --;
}

int main(){
	while(scanf("%d%d%d%d", &w, &h, &n, &m) != EOF){
		for(int i = 1; i <= n; i ++)
			rec[i].read();
		ans = 0;
		solve();
		if (m > 1){
			for(int i = 1; i <= n; i ++){
				swap(rec[i].x1, rec[i].y1);
				swap(rec[i].x2, rec[i].y2);
			}
			swap(w, h);
			solve();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
