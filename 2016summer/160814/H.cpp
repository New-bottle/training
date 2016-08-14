#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 210;
struct Poi{
	int x, y, z;
	LL dis;
	void read(){
		scanf("%d%d%d", &x, &y, &z);
	}
}p[N], a[N];
int n, cnt;
inline LL sqr(int x){
	return x * x;
}
inline LL dis(const Poi &a, const Poi &b){
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}
bool operator < (const Poi &a, const Poi &b){
	return a.dis < b.dis;
}

inline LL C(int n, int m){
	if (m == 2){
		return (LL)n * (n - 1) / 2;
	}
	return 0;
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) 
			p[i].read();
		LL ans = 0, mian = 0, zheng = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = i + 1; j <= n; j ++) {
				LL d = dis(p[i], p[j]);
				cnt = 0;
				for(int k = 1; k <= n; k ++) if (k != i && k != j)
					if (dis(p[i], p[k]) == dis(p[j], p[k])) {
						a[++ cnt] = p[k];
						a[cnt].dis = dis(p[i], p[k]);
					}
				sort(a + 1, a + cnt + 1);
				int len = 1;
				for(int k = 2; k <= cnt; k ++) {
					if (a[k].dis == a[k - 1].dis) len ++;
					else {
						ans += C(len, 2);
						len = 1;
					}
				}
				ans += C(len, 2);
				for(int k = 1; k <= cnt; k ++)
					if (dis(a[k], p[i]) == d) {
						for(int l = k + 1; l <= cnt; l ++) {
							if (dis(a[l], p[i]) != d) break;
							if (dis(a[l], a[k]) == d) zheng ++;
						}
					}
				for(int k = 1; k <= cnt; k ++)
					for(int l = k + 1; l <= cnt; l ++)
						if (a[l].dis == a[k].dis) {
							if (d + dis(a[k], a[l]) == 4 * a[k].dis)
								mian ++;
						}else break;
			}
//		printf("ans = %d mian = %d zheng = %d\n", ans, mian, zheng);
		ans /= 2;
		ans -= mian / 2;
		ans -= zheng / 3;
		cout << ans << endl;
	}
	return 0;
}
