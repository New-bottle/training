#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define debug

const int N = 210;

typedef long long LL;
const LL INF = 1e18;
int n, cnt = 1;
LL l;
struct Matrix {
	LL v[N][N];
	LL* operator [] (int x) {return v[x];}
	Matrix (int x = 0) {
		memset(v, 0, sizeof v);
	}
	friend Matrix operator * (const Matrix &a, const Matrix &b) {
		Matrix c;
		for(int i = 1; i <= cnt; i ++)
			for(int j = 1; j <= cnt; j ++) c[i][j] = -INF;
		for(int i = 1; i <= cnt; i ++)
			for(int k = 1; k <= cnt; k ++) if (a.v[i][k] != -INF)
				for(int j = 1; j <= cnt; j ++) if (b.v[k][j] != -INF)
					c[i][j] = max(c[i][j], a.v[i][k] + b.v[k][j]);
		return c;
	}
	void print() {
		for(int i = 1; i <= cnt; i ++) {
			for(int j = 1; j <= cnt; j ++)
				if (v[i][j] == -INF) printf(" - ");
				else printf("%2lld ", v[i][j] == -INF ? -1 : v[i][j]);
			puts("");
		}
	}
}a, f;

int ch[N][26], v[N], fail[N], b[N];
char s[N];
void Insert(int j) {
	scanf("%s", s + 1);
	int l = strlen(s + 1), x = 1, y;
	for(int i = 1; i <= l; i ++) {
		y = s[i] - 'a';
		if (!ch[x][y]) ch[x][y] = ++cnt;
		x = ch[x][y];
	}
	v[x] += b[j];
}
void bfs() {
	queue<int>Q;
	Q.push(1);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		v[x] += v[fail[x]];
		for(int i = 0; i < 26; i ++) {
			int j = fail[x];
			while(j && !ch[j][i]) j = fail[j];
			if (ch[x][i]) {
				int y = ch[x][i];
				fail[y] = ch[j][i] ? ch[j][i] : 1;
				Q.push(y);
			} else ch[x][i] = ch[j][i] ? ch[j][i] : 1;
		}
	}
}

void make_matrix() {
	for(int i = 1; i <= cnt; i ++)
		for(int j = 1; j <= cnt; j ++) a[i][j] = -INF;
	for(int i = 1; i <= cnt; i ++)
		for(int j = 0; j < 26; j ++)
			a[i][ch[i][j]] = v[ch[i][j]];
	for(int i = 1; i <= cnt; i ++) f[1][i] = -INF;
	f[1][1] = 0;
}
Matrix Pow(Matrix &a, LL b) {
	Matrix r;
	for(int i = 1; i <= cnt; i ++)
		for(int j = 1; j <= cnt; j ++)
			r[i][j] = (i == j) ? 0 : -INF;
	while(b) {
		if (b & 1) r = r * a;
		a = a * a;
		b >>= 1;
	}
	return r;
}

int main(){
	scanf("%d%lld", &n, &l);
	for(int i = 1; i <= n; i ++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i ++) Insert(i);
	bfs();
	make_matrix();
	f = f * Pow(a, l);
	LL ans = 0;
	for(int i = 1; i <= cnt; i ++) ans = max(ans, f[1][i]);
	printf("%lld\n", ans);
	return 0;
}
