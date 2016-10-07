#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#define N 10100
using namespace std;
int n, data[N];
struct Splay{
	struct node{
		int ch[2], pnt, size, min;
		int val;
		void clear(){
			ch[0] = ch[1] = pnt = size = min = 0;
			val = 0;
		}
	}tr[N];
	int root, tot;
	void newnode(int &x, int pnt){
		++ tot;
		tr[tot].clear();
		tr[tot].pnt = pnt;
		tr[tot].size = 1;
		x = tot;
	}
	
	void update(int x){
		int l = tr[x].ch[0], r = tr[x].ch[1];
		tr[x].size = tr[l].size + tr[r].size + 1;
		tr[x].min = tr[x].val;
		if(l) tr[x].min = min(tr[l].min, tr[x].min);
		if(r) tr[x].min = min(tr[r].min, tr[x].min);
	}
	
	void build(int &x, int l, int r, int pnt){
		newnode(x, pnt);
		int mid = l + r >> 1;
		tr[x].val = data[mid];
		if(l < mid) build(tr[x].ch[0], l, mid - 1, x);
		if(mid < r) build(tr[x].ch[1], mid + 1, r, x);
		update(x);
	}
	
	void init(){
		tr[0].clear();
		root = tot = 0;
		newnode(root, 0);
		newnode(tr[root].ch[1], root);
		build(tr[tr[root].ch[1]].ch[0], 1, n, tr[root].ch[1]);
		update(tr[root].ch[1]);
		update(root);
	}
	
	void rotate(int x, bool b){
		int y = tr[x].pnt;
		int z = tr[y].pnt;
		int son = tr[x].ch[b];
		tr[x].ch[b] = y;
		tr[y].ch[!b] = son;
		if(z) tr[z].ch[tr[z].ch[1] == y] = x;
		if(son) tr[son].pnt = y;
		tr[x].pnt = z;
		tr[y].pnt = x;
		update(y);
	}
	
	void splay(int x, int target){
		while(tr[x].pnt != target){
			int y = tr[x].pnt, z = tr[y].pnt;
			if(z == target){
				rotate(x, tr[y].ch[0] == x);
			}
			else{
				bool b = (tr[y].ch[0] == x), c = (tr[z].ch[0] == y);
				if(b == c) rotate(y, c), rotate(x, c);
				else rotate(x, b), rotate(x, c);
			}
		}
		update(x);
		if(target == 0) root = x;
	}
	
	void search(int x, int target){
		int pos = root;
		while(true){
			int l = tr[pos].ch[0], r = tr[pos].ch[1];
			if(tr[l].size + 1 == x){
				break;
			}
			if(x <= tr[l].size) pos = l;
			else{
				x = x - tr[l].size - 1;
				pos = r;
			}
		}
		splay(pos, target);
	}
	
	int find(int x){
		search(x, 0);
		int pos = tr[root].ch[1], res = tr[tr[root].ch[0]].size + 1;
		while(true){
			int l = tr[pos].ch[0], r = tr[pos].ch[1];
			if(tr[pos].val == x) return tr[l].size + 1 + res;
			if(l && tr[l].min == x){
				pos = l;
			}
			else{
				pos = r;
				res = res + tr[l].size + 1;
			}
		}
	}
	
	void change(int l, int r, int len){
		search(l, 0);
		search(l + len + 1, root);
		int t1 = tr[tr[root].ch[1]].ch[0];
		tr[tr[root].ch[1]].ch[0] = 0;
		update(tr[root].ch[1]);
		update(root);
		search(l, 0);
		search(l + len + 1, root);
		int t2 = tr[tr[root].ch[1]].ch[0];
		tr[tr[root].ch[1]].ch[0] = t1;
		tr[t1].pnt = tr[root].ch[1];
		update(tr[root].ch[1]);
		update(root);
		search(l, 0);
		search(l + 1, root);
		tr[tr[root].ch[1]].ch[0] = t2;
		tr[t2].pnt = tr[root].ch[1];
		update(tr[root].ch[1]);
		update(root);
	}
}sp;

vector< pair<int , int> > ans;

void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &data[i]);
	}
	sp.init();
	
	ans.clear();
	
	for(int i = 1; i <= n; i ++){	
		int pos = sp.find(i) - 1;
		while(pos != i){
			int len = pos - i + 1 >> 1;
			if((pos - i + 1) & 1){
				sp.change(i + 1, pos, len);
				ans.push_back(make_pair(i + 1, pos));
				pos = pos - len;
			}
			else{
				sp.change(i, pos, len);
				ans.push_back(make_pair(i, pos));
				pos = pos - len;
			}
		}
	}
	
	int sz = ans.size();
	printf("%d\n", sz);
	for(int i = 0; i < sz; i ++){
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}
int main(){	
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	return 0;
}
