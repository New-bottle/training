#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
const int N = 2010;
struct Rec{
	double x1, y1, x2, y2;
	void read(){
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	}
}a[N];

struct node{
	int l, r, rank;
	double y;
}q[N];
bool operator < (const node &a, const node &b) {
	return a.y < b.y || (fabs(a.y - b.y) < eps && a.rank < b.rank);
}

int n;
double v[N];
struct seg{
	double sum;
	int tag, min, max;
}t[N << 2];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o, int l, int r){
	t[o].min = min(t[L].min, t[R].min);
	t[o].max = max(t[L].max, t[R].max);
	t[o].sum = t[L].sum + t[R].sum;
	if (t[o].min > 1) t[o].sum = v[r] - v[l - 1];
}
void change(int o, int l, int r, int val){
	t[o].tag += val;
	t[o].max += val;
	t[o].min += val;
	if (t[o].min > 1) t[o].sum = v[r] - v[l - 1];
	else if (t[o].max > 1){
		change(lch, t[o].tag);
		change(rch, t[o].tag);
		t[o].tag = 0;
		Push_up(o, l, r);
	}else{
		t[o].sum = 0.0;
	}
}
void Push_down(int o, int l, int r){
	if (t[o].tag){
		change(lch, t[o].tag);
		change(rch, t[o].tag);
		t[o].tag = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, int v){
	if (ql <= l && qr >= r) change(o, l, r, v);
	else{
		Push_down(o, l, r);
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
		Push_up(o, l, r);
	}
}

int get(int l, int r, double x){
	if (fabs(x - v[mid]) < eps) return mid;
	if (x < v[mid]) return get(l, mid - 1, x);
	return get(mid + 1, r, x);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
			a[i].read();
			v[i] = a[i].x1;
			v[n + i] = a[i].x2;
		}
		sort(v + 1, v + n * 2 + 1);
		int num = 1, tot = n * 2;
		for(int i = 2; i <= tot; i ++)
			if (v[i] - v[num] > eps) v[++ num] = v[i];
		for(int i = 1; i <= n; i ++){
			q[n + i].l = q[i].l = get(1, num, a[i].x1);
			q[n + i].r = q[i].r = get(1, num, a[i].x2);
			q[i].y = a[i].y1;
			q[i].rank = 1;
			q[n + i].y = a[i].y2;
			q[n + i].rank = 2;
		}
		sort(q + 1, q + tot + 1);
		double ans = 0.0;
		for(int i = 1; i <= tot; i ++){
			if (q[i].y - q[i - 1].y > eps)
				ans += t[1].sum * (q[i].y - q[i - 1].y);
			if (q[i].rank == 1)
				update(1, 1, num, q[i].l + 1, q[i].r, 1);
			if (q[i].rank == 2)
				update(1, 1, num, q[i].l + 1, q[i].r, -1);
		}
		printf("%.2f\n", ans);
	}
	return 0;
}

