#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 200010;

int n, m, k;
struct poi {
	int x, y, id;
}p[N];
bool cmp1(const poi &a, const poi &b) {
	return (a.x + a.y) < (b.x + b.y);
}
bool cmp0(const poi &a, const poi &b) {
	return (a.y - a.x) < (b.y - b.x);
}
bool l[N], r[N], u[N], d[N], yes[N];
LL tm[N], k1[N], k0[N];
typedef pair<int,int> pii;
pii from1[N], from0[N];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i ++)
		scanf("%d%d", &p[i].x, &p[i].y), p[i].id = i;
	l[0] = l[m] = r[0] = r[m] = 
	u[0] = u[n] = d[0] = d[n] = 1;

	memset(k1, -1, sizeof k1);
	memset(k0, -1, sizeof k0);
	k1[100000] = 0;
	from1[100000] = make_pair(0, 0);

	int nx = 1, ny = 1, x = 0, y = 0, tx, ty, step;
	LL now = 0;
	while(1) {
//		printf("(%d, %d) now = %d\n", x, y, now);
		if (nx == 1) tx = n;
		else tx = 0;
		if (ny == 1) ty = m;
		else ty = 0;
		if (abs(x - tx) == abs(y - ty)) {
			;
			break;
		}
		if (abs(x - tx) < abs(y - ty)) {
			step = abs(x - tx);
			now += step;
			x += nx * step;
			y += ny * step;
			nx *= -1;
		} else {
			step = abs(y - ty);
			now += step;
			x += nx * step;
			y += ny * step;
			ny *= -1;
		}
		if (nx * ny > 0) {
			if (k1[y - x + 100000] != -1) break;
			else {
				k1[y - x + 100000] = now;
				from1[y - x + 100000] = make_pair(x, y);
			}
		} else {
			if (k0[x + y] != -1) break;
			else {
				k0[x + y] = now;
				from0[x + y] = make_pair(x, y);
			}
		}
	}
	for(int i = 1; i <= k; i ++) {
		LL ans = 1e18;
		int t1 = p[i].y - p[i].x + 100000, t0 = p[i].y + p[i].x;
		if (k1[t1] != -1) {
			ans = min(ans, k1[t1] + abs(from1[t1].first - p[i].x));
		}
		if (k0[t0] != -1) {
			ans = min(ans, k0[t0] + abs(from0[t0].first - p[i].x));
		}
		if (ans != (LL)1e18) printf("%lld\n", ans);
		else puts("-1");
	}
	return 0;
}
