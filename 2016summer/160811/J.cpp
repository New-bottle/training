#include<map>
#include<bitset>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include <unordered_map>
using namespace std;

const int P = 1e9 + 7;
struct node{
	int g[10];
	node(){memset(g, 0, sizeof g);}
};

bool operator < (const node &a, const node &b){
	for(int i = 1; i <= 8; i ++)
		if (a.g[i] != b.g[i]) return a.g[i] < b.g[i];
	return 0;
}

bool operator == (const node &a, const node &b){
	for(int i = 1; i <= 8; i ++)
		if (a.g[i] != b.g[i]) return false;
	return true;
}

struct H {
	size_t operator () (const node& a) const {
		size_t ans = 0;
		for(int i = 1; i <= 8; i ++)
			ans = (ans << 4) + a.g[i];
		return ans;
	}
};

char s[11][11];
//bitset<11> mp[11];
int mp[11];
unordered_map<node, int, H> f[11][11];
unordered_map<node, int, H> :: iterator it;

int main(){
	int T, n;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) {
			scanf("%s", s[i] + 1);
			mp[i] = 0;
			for(int j = 1; j <= n; j ++)
				if (s[i][j] == 'o') mp[i] |= (1 << j);
//				mp[i][j] = s[i][j] == 'o';
//			cout << mp[i] << endl;
		}

		node t, tmp;
		for(int i = 0; i <= n; i ++) t.g[i] = 0;
		f[0][0][t] = 1;
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j <= n; j ++) f[i + 1][j].clear();
			for(int j = 0; j <= n; j ++){
				for(it = f[i][j].begin(); it != f[i][j].end(); ++it)
					for(int mask = 0; mask < (1 << n); mask ++) 
						if (((mask << 1) & mp[i + 1]) == (mask << 1)) {
//						if ((bitset<11>(mask << 1) & mp[i + 1]) == bitset<11>(mask << 1)){
							int nj = j;
							int arr[11];
							std::memcpy(arr, it->first.g, sizeof(arr));
							for(int k = 1; k <= n; k ++) if ((mask << 1) >> k & 1) {
								tmp.g[k] = min(tmp.g[k - 1], min(arr[k], arr[k - 1])) + 1;
								nj = max(nj, tmp.g[k]);
							} else tmp.g[k] = 0;
							f[i + 1][nj][tmp] = (f[i + 1][nj][tmp] + it -> second) % P;
						}
			}
		}
		int ans = 0;
		for(int j = 0; j <= n; j ++) {
			ans = 0;
			for(it = f[n][j].begin(); it != f[n][j].end(); ++it)
				ans = (ans + it -> second) % P;
			printf("%d\n", ans);
		}
	}
	return 0;
}
