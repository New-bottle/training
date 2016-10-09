#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, m, k, ch, cv;
struct hor {
	int x, y1, y2;
	bool operator < (const hor &b) const {
		return y1 < b.y1 || (y1 == b.y1 && y2 > b.y2);
	}
}h[N];
struct ver {
	int y, x1, x2;
	bool operator < (const ver &b) const {
		return x1 < b.x1 || (x1 == b.x1 && x2 > b.x2);
	}
}v[N];

bool vish[N], visv[N];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i ++) {
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 == x2) {
			if (y1 > y2) swap(y1, y2);
			h[++ch] = (hor){x1, y1, y2};
		} else {
			if (x1 > x2) swap(x1, x2);
			v[++cv] = (ver){y1, x1, x2};
		}
	}
	sort(h + 1, h + ch + 1);
	int ans = 0;
	int len = 0, num = 0, maxy = 0, maxx = 0;
	for(int i = 1; i <= ch; i ++) {
		vish[h[i].x] = 1;
		if (h[i].x != h[i - 1].x) {
			ans ^= m - len;
			num ++;
			len = h[i].y2 - h[i].y1;
			maxy = h[i].y2;
		} else {
			len += max(0, h[i].y2 - max(h[i].y1, maxy));
			maxy = max(maxy, h[i].y2);
		}
	}
	if (ch) ans ^= m - len;
	if ((n - num - 1) & 1) ans ^= m;

	sort(v + 1, v + cv + 1);
	len = num = maxy = 0;
	for(int i = 1; i <= cv; i ++) {
		visv[v[i].y] = 1;
		if (v[i].y != v[i - 1].y) {
			ans ^= n - len;
			num ++;
			len = v[i].x2 - v[i].x1;
			maxx = v[i].x2;
		} else {
			len += max(0, v[i].x2 - max(v[i].x1, maxx));
			maxx = max(maxx, v[i].x2);
		}
	}
	if (cv) ans ^= n - len;
	if ((m - num - 1) & 1) ans ^= n;
	if (ans) {
		puts("FIRST");
		bool sign = 0;
		for(int i = 1; i < n; i ++) 
			if (!vish[i] && m >= (ans ^ m)) {
				printf("%d 0 %d %d\n", i, i, m - (ans ^ m));
				sign = 1;
				break;
			}
		if (!sign) {
			for(int i = 1; i < m; i ++)
				if (!visv[i] && n >= (ans ^ n)) {
					printf("%d 0 %d %d\n", i, i, n - (ans ^ n));
					break;
				}
		}
	} else puts("SECOND");
	return 0;
}
