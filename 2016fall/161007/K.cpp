#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

const int N = 30;
int n;

char obuf[100][100];
char s[100];

int mp[N][N];
int b[N];
bool inq[N];
int prd[N];
int d[N];

std::pair<int, int> spfa(int S) {
	queue<int>Q;
	memset(d, 0, sizeof d);
	memset(b, 0, sizeof b);
	memset(inq, 0, sizeof inq);
	Q.push(S);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		b[x] ++;
		if (b[x] > 27) return {-1, x};
		for(int i = 0; i < 26; i ++)
			if (mp[x][i] != 0 && d[i] > d[x] + mp[x][i]) {
				prd[i] = x;
				d[i] = d[x] + mp[x][i];
				if (!inq[i]) {
					inq[i] = 1;
					Q.push(i);
				}
			}
	}
	int ans = 0;
	int pos = 0;
	for(int i = 0; i < 26; i ++)
		if (ans > d[i]) ans = d[i], pos = i;
	return {-ans, pos};
}

void circle(int node)
{
	//std::cout << "Circle" << std::endl;
	int p = 19;
	for (int t = 0; t < 40; ++t) {
		int k = p;
		int l = 19;
		for (int i = 0; i < 40; ++i) {
			//std::cout << k << ' ' << l << std::endl;
			if (k >= 0 && l >= 0)
				obuf[l][k] = node + 'a';
			++k;
			--l;
		}
		--p;
		node = prd[node];
	}
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			std::cout << obuf[i][j];
		}
		std::cout << std::endl;
	}
}

void chain(int len, int node)
{
	//std::cout << "CHAIN " << len << "\n";
	int dim = (len - 1) / 2;
	int p = dim;
	for (int i = 0; i < len; ++i) {
		int k = p;
		int l = dim;
		for (int i = 0; i < 40; ++i) {
			//std::cout << k << ' ' << l << std::endl;
			//std::cout << k << ' ' << l << std::endl;
			if (k >= 0 && l >= 0)
				obuf[l][k] = node + 'a';
			++k;
			--l;
		}
		--p;
		node = prd[node];
	}
	for (int i = 0; i <= dim; ++i) {
		for (int j = 0; j <= dim; ++j) {
			std::cout << obuf[i][j];
		}
		std::cout << std::endl;
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &n);
		memset(mp, 0, sizeof mp);
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s);
			int x = s[0] - 'a', y = s[1] - 'a';
			mp[x][y] = -1;
		}
		for(int i = 0; i < 26; i ++)
			for(int j = 0; j < 26; j ++)
				mp[i][j] = -1 - mp[i][j];
		bool flag = false;
		std::pair<int, int> bns;
		int cns;
		for(int i = 0; i < 26; i ++) {
			auto ans = spfa(i);
			if (ans.first < 0) {
				flag = true;
				circle(ans.second);
				break;
			} else {
				if (ans > bns) {
					bns = ans;
					cns = i;
				}
			}
		}
		if (flag)
			continue;
		//std::cout << bns.first << ' ' << bns.second << std::endl;
		auto ans = spfa(cns);
		chain(ans.first + 1, ans.second);
	}
	return 0;
}
