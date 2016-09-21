#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define INF 0x3f3f3f3f
#define N 300010
#define M 150010
#define L (x << 1)
#define R (x << 1 | 1)
using namespace std;
int data[N], sum[N];
struct Segment_Tree{
	struct node{
		int sum, size;
		int mark;
	}tr[N << 2];
	void update(int x){
		int ls = L, rs = R;
		tr[x].size = tr[ls].size + tr[rs].size;
		tr[x].sum = min(tr[ls].sum, tr[rs].sum);
	}
	void build(int l, int r, int x){
		tr[x].sum = tr[x].size = 0;
		tr[x].mark = 0;
		if(l == r){
			tr[x].sum = sum[l];
			tr[x].size = (data[l] == -1 ? 1 : 0);
		}
		if(l < r){
			int  mid = l + r >> 1;
			build(l, mid, L);
			build(mid + 1, r, R);
			update(x);
		}
	}
	void push_down(int x){
		if(tr[x].mark == 0) return;
		int ls = L, rs = R;
		tr[ls].sum = tr[ls].sum + tr[x].mark;
		tr[ls].mark += tr[x].mark;
		tr[rs].sum = tr[rs].sum + tr[x].mark;
		tr[rs].mark += tr[x].mark;
		tr[x].mark = 0;
	}
	void modify_sum(int x, int l, int r, int a, int b, int ad){
		if(a <= l && r <= b){
			tr[x].mark += ad;
			tr[x].sum += ad;
			return;
		}
		push_down(x);
		int mid = l + r >> 1;
		if(a <= mid) modify_sum(L, l, mid, a, b, ad);
		if(b > mid) modify_sum(R, mid + 1, r, a, b, ad);
		update(x);
	}
	void modify_size(int x, int l, int r, int pos, int ad){
		if(l == r){
			tr[x].size += ad;
			return;
		}
		int mid = l + r >> 1;
		push_down(x);
		if(pos <= mid) modify_size(L, l, mid, pos, ad);
		else modify_size(R, mid + 1, r, pos, ad);
		update(x);
	}
	int query_sum(int x, int l, int r){
		if(l == r) return tr[x].sum < 2 ? INF : l;
		int mid = l + r >> 1;
		push_down(x);
		int res = INF;
		if(tr[R].sum >= 2) res = min(mid + 1, query_sum(L, l, mid));
		else res = query_sum(R, mid + 1, r);
		update(x);
		return res;
	}
	int query_size(int x, int l, int r){
		if(tr[x].size == 0) return INF;
		if(l == r) return l;
		int mid = l + r >> 1;
		push_down(x);
		int res;
		if(tr[L].size) res = query_size(L, l, mid);
		else res = query_size(R, mid + 1, r);
		update(x);
		return res;
	}
	int query(int x, int l, int r, int pos){
		if(l == r) return tr[x].sum;
		int mid = l + r >> 1;
		push_down(x);
		int res;
		if(pos <= mid) res = query(L, l, mid, pos);
		else res = query(R, mid + 1, r, pos);
		update(x);
		return res;
	}
}sg;
int n, q;
char str[N];
int br(char c){
	return c == '(' ? 1 : -1;
}
void solve(){
	scanf("%d", &q);
	scanf("%s", str + 1);
	for(int i = 1; i <= n; i ++){
		data[i] = br(str[i]);
		sum[i] = sum[i - 1] + data[i];
	}
	sg.build(1, n, 1);
	for(int i = 1; i <= q; i ++){
		int t;
		scanf("%d", &t);
		int tmp;
		if(str[t] == '('){
			str[t] = ')';
			sg.modify_size(1, 1, n, t, 1);
			sg.modify_sum(1, 1, n, t, n, -2);
			int pos = sg.query_size(1, 1, n);
			str[pos] = '(';
			sg.modify_size(1, 1, n, pos, -1);
			sg.modify_sum(1, 1, n, pos, n, 2);
			printf("%d\n", pos);
		}
		else{
			str[t] = '(';
			sg.modify_size(1, 1, n, t, -1);
			sg.modify_sum(1, 1, n, t, n, 2);
			int pos = sg.query_sum(1, 1, n);
			str[pos] = ')';
			sg.modify_size(1, 1, n, pos, 1);
			sg.modify_sum(1, 1, n, pos, n, -2);
			printf("%d\n", pos);
		}
	}
}
int main(){
	while(scanf("%d", &n) == 1){
		solve();
	}
}
