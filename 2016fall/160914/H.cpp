#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
typedef long double ldb;
const int N = 110;
bool yes[N], vis[N];
struct poi{
	ldb x, y, r;
};

#define sqr(x) ((x) * (x))
vector<poi> p;
vector<poi> merge(vector<poi> p) {
	vector<poi>ans;
	memset(yes, 0, sizeof yes);
	poi now = p[p.size() - 1];
	ldb x = now.x, y = now.y, r = now.r * now.r;
	int num = 1;
	
	for(int i = 0; i < p.size() - 1; i ++)
		if (sqr(p[i].r) >= sqr(p[i].x - now.x) + sqr(p[i].y - now.y) ||
			sqr(now.r ) >= sqr(p[i].x - now.x) + sqr(p[i].y - now.y)) {
			yes[i] = 1;
			x += p[i].x;
			y += p[i].y;
			r += sqr(p[i].r);
			num ++;
		}
	for(int i = 0; i < p.size() - 1; i ++)
		if (!yes[i]) ans.push_back(p[i]);
	ans.push_back((poi){1.0 * x / num, 1.0 * y / num, sqrt(r)});
	return ans;
}

int main(){
	int n;
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 1; i <= n; i ++) {
			int x, y, r;
			scanf("%d%d%d", &x, &y, &r);
			poi t;
			t.x = x; t.y = y; t.r = r;
			p.push_back(t);
			int tmp;
			do{
				tmp = p.size();
				p = merge(p);
			}while (p.size() < tmp);
		}
		printf("%d\n", p.size());
		p.clear();
	}
	return 0;
}
