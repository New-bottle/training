#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 300010;
struct poi{
	int a, b;
	void read(){
		scanf("%d%d", &a, &b);
	}
}p[N];
bool operator < (const poi &a, const poi &b){
	return a.a < b.a || (a.a == b.a && a.b < b.b);
}

LL Pow(LL a, LL b){
	LL r = 1;
	while(b){
		if (b & 1) r = r * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return r;
}
int va[N], vb[N], numa, numb, n;

struct node{
	int sumcnt;
	LL sumv, mul;
}t[N << 2];
#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
#define lch L, l, mid
#define rch R, mid + 1, r
void Push_up(int o){
	t[o].sumcnt = t[L].sumcnt + t[R].sumcnt;
	t[o].sumv = (t[L].sumv + t[R].sumv) % P;
}
void change(int o, int val){
	t[o].sumv = t[o].sumv * val % P;
	t[o].mul = t[o].mul * val % P;
}
void Push_down(int o){
	if (t[o].mul != 1){
		change(L, t[o].mul);
		change(R, t[o].mul);
		t[o].mul = 1;
	}
}
int query(int o, int l, int r, int ql, int qr){
	if (ql <= l && qr >= r) return t[o].sumcnt;
	else{
		Push_down(o);
		int ans = 0;
		if (ql <= mid) ans += query(lch, ql, qr);
		if (qr >  mid) ans += query(rch, ql, qr);
		return ans;
	}
}
void update(int o, int l, int r, int pos){
	if (l == r){
		t[o].sumcnt ++;
	}else{
		Push_down(o);
		if (pos <= mid) update(lch, pos);
		else update(rch, pos);
		Push_up(o);
	}
}
void updatev(int o, int l, int r, int pos){
	if (l == r){
		t[o].sumv = (Pow(2, query(1, 1, n, 1, pos)) - 1) * Pow(3, vb[pos]) % P;
	}else{
		Push_down(o);
		if (pos <= mid) updatev(lch, pos);
		else updatev(rch, pos);
		Push_up(o);
	}
}
void modify(int o, int l, int r, int ql, int qr){
	if (ql > qr) return;
	if (ql <= l && qr >= r) change(o, 2);
	else{
		Push_down(o);
		if (ql <= mid) modify(lch, ql, qr);
		if (qr >  mid) modify(rch, ql, qr);
		Push_up(o);
	}
}
LL tmp;
void queryv(int o, int l, int r, int ql, int qr){
	if (ql <= l && qr >= r) tmp = (tmp + t[o].sumv) % P;
	else{
		Push_down(o);
		if (ql <= mid) queryv(lch, ql, qr);
		if (qr >  mid) queryv(rch, ql, qr);
	}
}

void pre(){
	memset(t, 0, sizeof t);
	for(int i = 1; i <= n * 4; i ++) t[i].mul = 1;
	for(int i = 1; i <= n; i ++) va[i] = p[i].a, vb[i] = p[i].b;
	sort(va + 1, va + n + 1);
	numa = unique(va + 1, va + n + 1) - va - 1;
	for(int i = 1; i <= n; i ++) p[i].a = lower_bound(va + 1, va + numa + 1, p[i].a) - va;
	sort(vb + 1, vb + n + 1);
	numb = unique(vb + 1, vb + n + 1) - vb - 1;
	for(int i = 1; i <= n; i ++) p[i].b = lower_bound(vb + 1, vb + numb + 1, p[i].b) - vb;
	sort(p + 1, p + n + 1);
}
int main(){
	while(scanf("%d", &n) == 1){
		for(int i = 1; i <= n; i ++) p[i].read();
		pre();
//		for(int i = 1; i <= n; i ++) printf("%d %d\n",p[i].a, p[i].b);
		int ans = 0;
		LL now = 0;
		for(int i = 1; i <= n; i ++){
			now = Pow(2, query(1, 1, n, 1, p[i].b)) * Pow(3, va[p[i].b]) % P;
			update(1, 1, n, p[i].b);
			updatev(1,1,n,p[i].b);
			tmp = 0;
			queryv(1 ,1, n, p[i].b + 1, n);
			ans = ((LL)ans + ((now + tmp) % P) * Pow(2, va[p[i].a]) % P) % P;
//			cout << "tmp = " << tmp * Pow(2, va[p[i].a]) % P << endl;
//			cout << "ans = " << ans << endl;
			modify(1, 1, n, p[i].b + 1, n);
		}
		printf("%d\n",ans);
	}
	return 0;
}
