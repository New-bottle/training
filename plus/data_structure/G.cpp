#include<cstdio>
#include<set>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200010;

int n, ans[N << 4][2], cnt;
struct node{
	int h, l, r;
}a[N];
struct Event {
	int x, y, rank;
	bool operator < (const Event &b) const {
		return x < b.x || (x == b.x && rank > b.rank) ||
			(x == b.x && rank == b.rank && rank == 0 && y < b.y) ||
			(x == b.x && rank == b.rank && rank == 1 && y > b.y);
		//insert-check-delete-check
	}
}e[N << 1];

int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d%d", &a[i].h, &a[i].l, &a[i].r);
	int tot = 0;
	for(int i = 1; i <= n; i ++) {
		e[++ tot] = (Event){a[i].l, a[i].h, 1};
		e[++ tot] = (Event){a[i].r, a[i].h, 0};
	}
	
	sort(e + 1, e + tot + 1);
//	for(int i = 1; i <= tot; i ++) printf("%d %d %d\n", e[i].x, e[i].y, e[i].rank);
	multiset<int>s;
	int nowy = 0, lasty = 0;
	for(int i = 1; i <= tot; i ++) {
		if (e[i].rank == 1) s.insert(e[i].y);
		else s.erase(s.find(e[i].y));
		lasty = nowy;
		if (s.size()) nowy = *s.rbegin();
		else nowy = 0;
		if (lasty == nowy) continue;
		if (lasty != nowy) {
			++ cnt;
			ans[cnt][0] = e[i].x; ans[cnt][1] = lasty;
		}
		++ cnt;
		ans[cnt][0] = e[i].x; ans[cnt][1] = nowy;
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i ++) printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
