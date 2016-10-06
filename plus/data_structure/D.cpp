#include<cstdio>
#include<set>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;
const int M = 1e6 + 10;

struct node {
	int x, dis;
	bool operator < (const node &b) const {
		return dis < b.dis || (dis == b.dis && x > b.x);
	}
};
priority_queue<node>Q;
typedef pair<int,int> pii;
set<pii >s;
set<int>used;
set<pii >::iterator it;
//first -> pos second -> dis 

int n, m, pos[M], id[N], num = 0;
int dis[N];

inline pii findpos(int l, int r) {
	if (l == 1) return make_pair(1, r - 1);
	if (r == n) return make_pair(n, n - l);
	return make_pair((l + r) / 2, (r - l) / 2);
}//pos dis
int getpos() {
	set<int>::iterator it;
	int ans = 0;
	int x = Q.top().x, d = Q.top().dis; Q.pop();
	while(s.find(make_pair(x, d)) == s.end()) {
		x = Q.top().x, d = Q.top().dis; Q.pop();
	}
	s.erase(s.find(make_pair(x, d)));
	ans = x;
	it = used.lower_bound(x);
	if ((*it) - 1 > x) {
		pii tmp = findpos(x + 1, *it - 1);
		s.insert(tmp);
		Q.push((node){tmp.first, tmp.second});
	}
	it --;
	if ((*it) + 1 < x) {
		pii tmp = findpos(*it + 1, x - 1);
		s.insert(tmp);
		Q.push((node){tmp.first, tmp.second});
	}
	used.insert(x);
	return ans;
}

void Remove(int p) {
	used.erase(p);
	num --;
//	used[p] = 0;
	int nl, nr;
	set<int>::iterator t;
	t = used.lower_bound(p); nr = (*t) - 1;
	t --; nl = (*t) + 1;

	set<pii >::iterator it;
	it = s.lower_bound(make_pair(p, n + 1));
//	if (it -> first <= n) s.erase(it);
	if (it -> first > p && it -> first <= nr) s.erase(it);

	it = s.lower_bound(make_pair(p, n + 1));
	--it;
//	if (it -> first >= 1) s.erase(it);
	if (it -> first >= nl && it -> first < p) s.erase(it);

	pii tmp = findpos(nl, nr);
	s.insert(tmp);
	Q.push((node){tmp.first, tmp.second});
}

int main(){
	scanf("%d%d", &n, &m);
	used.insert(0);
	used.insert(n + 1);
	s.insert(make_pair(0, -1));
	s.insert(make_pair(n + 1, -1));
	s.insert(make_pair(1, n + 1));
	Q.push((node){1, n + 1});

	for(int i = 1; i <= m; i ++) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		if (opt == 1) {
			int p = getpos();
			printf("%d\n", p);
			cout << flush;
			pos[x] = p;
			id[p] = x;
		} else {
			Remove(pos[x]);
			id[pos[x]] = 0;
			pos[x] = 0;
		}
	}
	return 0;
}
