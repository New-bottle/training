#include<cstdio>
#include<vector>
#include<set>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 400010;
struct node{
	int x, y, col;
	void read(){
		scanf("%d%d%d", &x, &y, &col);
	}
}a[N];
bool operator < (const node &a, const node &b){
	return a.y < b.y;
}
int n, m, v[N], numy, numx;
set<int>s[N];
set<int>::iterator it;
vector<int>have[N];

void lisanhua(){
	for(int i = 1; i <= n; i ++) v[i] = a[i].x;
	sort(v + 1, v + n + 1);
	numx = unique(v + 1, v + n + 1) - v - 1;
	for(int i = 1; i <= n; i ++)
		a[i].x = lower_bound(v + 1, v + numx + 1, a[i].x) - v;

	for(int i = 1; i <= n; i ++) v[i] = a[i].y;
	sort(v + 1, v + n + 1);
	numy = unique(v + 1, v + n + 1) - v - 1;
	for(int i = 1; i <= n; i ++)
		a[i].y = lower_bound(v + 1, v + numy + 1, a[i].y) - v;
}

int bit[N];
void add(int x){
	for(;x <= numx; x += x & (-x)) bit[x] ++;
}
int sum(int x){
	int r = 0;
	for(;x; x -= x & (-x)) r += bit[x];
	return r;
}

void init(){
	scanf("%d%d", &n, &m);
	memset(bit, 0, sizeof bit);
	for(int i = 1; i <= n; i ++)
		a[i].read();
	lisanhua();
	for(int i = 1; i <= m; i ++){
		s[i].insert(0);
		s[i].insert(numx + 1);
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		init();
		sort(a + 1, a + n + 1);
		for(int i = 1; i <= n; i ++) have[a[i].y].push_back(i);
		int ans = 0, x;
		for(int y = 1; y <= numy; y ++){
			for(int j = 0; j < have[y].size(); j ++){
				int l, r, c = a[have[y][j]].col, x = a[have[y][j]].x;
				it = s[c].lower_bound(x);
				r = *it;
				it --;
				l = *it;
				if (l > r) continue;
				ans = max(ans, sum(r - 1) - sum(l));
			}
			for(int j = 0; j < have[y].size(); j ++){
				add(a[have[y][j]].x);
				s[a[have[y][j]].col].insert(a[have[y][j]].x);
			}
		}
		for(int i = 1; i <= m; i ++){
			it = s[i].begin();
			while(*it != numx + 1){
				int l, r;
				l = *it + 1;
				it ++;
				r = *it - 1;
				if (l > r) continue;
				ans = max(ans, sum(r) - sum(l - 1));
			}
		}
		printf("%d\n", ans);
		for(int i = 0; i <= numy; i ++) have[i].clear();
		for(int i = 0; i <= m; i ++) s[i].clear();
	}
	return 0;
}
