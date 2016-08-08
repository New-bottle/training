#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;

#define forceinline __inline__ __attribute__((always_inline))

const int N = 200010;
int n, v[N], a[N], last[N], nxt[N], l[N], r[N];

struct Event{
	int l, r;
};
vector<Event>ad[N], de[N];

struct node{
	int min, max, sum, tag;
}t[N << 2];
#define mid ((l + r) >> 1)
#define L (o << 1)
#define R (o << 1 | 1)
#define lch L, l, mid
#define rch R, mid + 1, r

forceinline void Push_up(int o, int l, int r){
	t[o].min = min(t[L].min, t[R].min);
	t[o].max = max(t[L].max, t[R].max);
	t[o].sum = t[L].sum + t[R].sum;
	if (t[o].min >= 1) t[o].sum = r - l + 1;
}
void change(int o, int l, int r, int val){
	t[o].min += val;
	t[o].max += val;
	t[o].tag += val;
	if (t[o].min >= 1) t[o].sum = r - l + 1;
	else if (t[o].max > 0){
		change(lch, val);
		change(rch, val);
		Push_up(o, l, r);
	}else{
		t[o].sum = 0;
	}
}

forceinline void Push_down(int o, int l, int r){
	if (t[o].tag){
		change(lch, t[o].tag);
		change(rch, t[o].tag);
		t[o].tag = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, int val){
	if (ql <= l && qr >= r) change(o, l, r, val);
	else{
		Push_down(o, l, r);
		if (ql <= mid) update(lch, ql, qr, val);
		if (qr >  mid) update(rch, ql, qr, val);
		Push_up(o, l, r);
	}
}

void init(){
	scanf("%d", &n);
	int num = 0;
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
		v[i] = a[i];
		last[i] = 0;
		nxt[i] = n + 1;
	}
	sort(v + 1, v + n + 1);
	num = unique(v + 1, v + n + 1) - v - 1;
	for(int i = 1; i <= n; i ++)
		a[i] = lower_bound(v + 1, v + num + 1, a[i]) - v;

	for(int i = 1; i <= n; i ++){
		l[i] = last[a[i]] + 1;
		last[a[i]] = i;
	}
	for(int i = n; i; i --){
		r[i] = nxt[a[i]] - 1;
		nxt[a[i]] = i;
	}
//	for(int i = 1; i <= n; i ++) printf("%d %d\n", l[i], r[i]);
}

//rec : x -> (l[i], i), y -> (i, r[i])
void cleartree()
{
		memset(t, 0, sizeof t);
}
void work(){
	for(int i = 1; i <= n; i ++) ad[i].clear(), de[i].clear();
	for(int i = 1; i <= n; i ++){
		ad[i].push_back((Event){l[i], i});
		de[r[i]].push_back((Event){l[i], i});
	}
/*	if (n == 1){
		for(int j = 0; j < ad[1].size(); j ++)
			printf("%d %d\n", ad[1][j].l, ad[1][j].r);
		for(int j = 0; j < ad[1].size(); j ++)
			printf("%d %d\n", de[1][j].l, de[1][j].r);
	}
*/	for(int i = 1; i <= n; i ++){
		for(int j = 0; j < ad[i].size(); j ++)
			update(1, 1, n, ad[i][j].l, ad[i][j].r, 1);
//		printf("t[1].sum = %d\n", t[1].sum);
		if (t[1].sum < i){
			puts("boring");
			cleartree();
			return;
		}
		for(int j = 0; j < de[i].size(); j ++)
			update(1, 1, n, de[i][j].l, de[i][j].r, -1);
	}
	puts("non-boring");
}
int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		init();
		work();
	}
	return 0;
}
