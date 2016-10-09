#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 100001
using namespace std;
namespace Segment_Tree{
	struct node{
		node *ls, *rs;
		int size;
		void *operator new(size_t, node *ls, node *rs, int s);	
	}mempool[N * 10], *cnt = mempool, *tree[N];
	void* node :: operator new(size_t, node *ls, node *rs, int s){
		cnt -> ls = ls;
		cnt -> rs = rs;
		cnt -> size = s;
		return cnt ++;
	}
	node *insert(node *p, int l, int r, int pos, int ad){
		if(l == r) return new(0x0, 0x0, p -> size + ad)node;
		int mid = l + r >> 1;
		if(pos <= mid) return new(insert(p -> ls, l, mid, pos, ad), p -> rs, p -> size + ad)node;
		else return new(p -> ls, insert(p -> rs, mid + 1, r, pos, ad), p -> size + ad)node;
	}
	int query(node *p1, node *p2, int l, int r, int a, int b){
		if(a <= l && r <= b){
			return (p1 -> size) - (p2 -> size);
		}
		int mid = l + r >> 1;
		int res = 0;
		if(a <= mid) res = res + query(p1 -> ls, p2 -> ls, l, mid, a, b);
		if(b > mid) res = res + query(p1 -> rs, p2 -> rs, mid + 1, r, a, b);
		return res;
	}
}
using namespace Segment_Tree;
void init(){
	cnt = mempool;
	tree[0] = new(0x0, 0x0, 0)node;
	tree[0] -> ls = tree[0] -> rs = tree[0];
}
int pos[N];
int data[N];
int n, m;
void solve(){
	scanf("%d%d", &n, &m);
	pos[0] = 0;
	for(int i = 1; i <= n; i ++){
		scanf("%d", &data[i]);
		pos[data[i]] = i;
	}
	for(int i = 1; i <= n; i ++){
		tree[i] = tree[i - 1];
		tree[i] = insert(tree[i], 0, n, pos[data[i] - 1], 1);
	}
	for(int i = 1; i <= m; i ++){
		int a, b;
		scanf("%d%d", &a, &b);
		int res = 0;
		res = res + query(tree[b], tree[a - 1], 0, n, 0, a - 1);
		if(b != n) res = res + query(tree[b], tree[a - 1], 0, n, b + 1, n);
		printf("%d\n", res);
	}
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		init();
		solve();
	}
	return 0;
}
