#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 610;
const int INF = 0x3c3c3c3c;
int n;

int v[N << 1];
struct Seg{
	int l, r, d;
	void read() {
		scanf("%d%d%d", &l, &r, &d);
	}
	friend bool operator < (const Seg &a, const Seg &b) {
		return a.d > b.d;
	}
}seg[N];

int cnt, dp[N][N];
bool sign[N];
int solve(int l, int r) {
	//std::cout << l << ' ' <<r << std::endl;
	if (r - l < 1)
		return 0;
	int& ans = dp[l][r];
	if (ans >= 0) return ans;
	int who = 0;
	int md = 0;
	for(int i = 1; i <= n; i ++) {
		sign[i] = 0;
		//std::cout << seg[i].l << ' ' << seg[i].r << ' ' <<seg[i].d << endl;
		if (seg[i].l > l && seg[i].r < r) {
			who = i;
			md = seg[i].d;
			break;
		}
	}
	if (who == 0) return ans = 0;
	//std::cout << md << std::endl;
	
	ans = INF;
	for(int i = seg[who].l; i <= seg[who].r; i ++) {
		ans = min(ans, md + solve(l, i) + solve(i, r));
	}
	//std::cout << "Solve " << l << ' ' << r << " = " << ans << std::endl;
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --) {
		memset(dp, -1, sizeof dp);
		scanf("%d", &n);
		cnt = 0;
		for(int i = 1; i <= n; i ++) {
			seg[i].read();
			v[++cnt] = seg[i].l;
			v[++cnt] = seg[i].r;
		}
		sort(v + 1, v + cnt + 1);
		cnt = unique(v + 1, v + cnt + 1) - v - 1;
		for(int i = 1; i <= n; i ++) {
			seg[i].l = lower_bound(v + 1, v + cnt + 1, seg[i].l) - v;
			seg[i].r = lower_bound(v + 1, v + cnt + 1, seg[i].r) - v;
		}
		sort(seg + 1, seg + n + 1);
		int ans = solve(0, cnt + 1);
		printf("%d\n", ans);
	}
	return 0;
}
