#include<cstdio>
#include<unordered_map>
#include<map>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 60010;
string s[N], tmp;
unordered_map<string, int> mp;
unordered_map<string, int>:: iterator it;
//char s[N][12], tmp[12];
int dis[N], n, from[N];
bool vis[N];
queue<int>Q;

int ans[N];
void output(){
	int t = n, cnt = 0;
	while(t != 1){
		ans[++ cnt] = t;
		t = from[t];
	}
	cout << s[1] << endl;
	for(int i = cnt; i; i --) cout << s[ans[i]] << endl;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i ++){
		getline(cin, s[i]);
		cin >> s[i];
		mp[s[i]] = i;
	}
	Q.push(1);
	vis[1] = 1;
	dis[1] = 1;
	int l = s[1].length(), x, y;
	while(!Q.empty()){
		x = Q.front(); Q.pop();
		tmp = s[x];
		for(int i = 0; i < l; i ++){
			char ch = tmp[i];
			for(int j = 0; j < 26; j ++){
				tmp[i] = (char)('a' + j);
				it = mp.find(tmp);
				if (it != mp.end()){
					y = it -> second;
					if (!vis[y]){
						Q.push(y);
						from[y] = x;
						vis[y] = 1;
						dis[y] = dis[x] + 1;
						if (y == n){
							cout << dis[n] << endl;
							output();
							return 0;
						}
					}
				}
			}
			tmp[i] = ch;
		}
	}
	cout << "FAIL" << endl;
	return 0;
}
