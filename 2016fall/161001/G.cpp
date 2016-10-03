#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#define LL long long
#define N 200010
#define M 5000010
using namespace std;
vector<string> data;
string str;
struct AC_Automation{
	int tr[N][2], g[N], tot, End[N];
	int mark;
	bool flag;
	void init(){
		for(int i = 1; i <= tot; i ++) tr[i][0] = tr[i][1] = g[i] = End[i] = 0;
		tot = 1;
		flag = 1;
		g[1] = 0;
	}
	void add(int x, int y, int len){
		if(y > len){
			End[x] ++;
			return;
		}
		int &cur = tr[x][str[y] - '0'];
		if(cur == 0) cur = ++ tot;
		add(cur, y + 1, len);
	}
	queue<int> q;
	void bfs(){
		g[1] = 0;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i = 0; i < 2; i ++){
				int y;
				if(y = tr[u][i]){
					int j;
					for(j = g[u]; j; j = g[j]) if(tr[j][i]) break;
					if(tr[j][i]){
						g[y] = tr[j][i];
						End[y] += End[g[y]];
					}	
					else g[y] = 1;
					q.push(y);
				}
			}
		}
	}
	LL search(int x, int y, int len){
		int cur = str[y] - '0';
		if(y > len) return 0;
		if(!x) return search(1, y + 1, len);
		LL res = End[x];
		if(tr[x][cur]) res = res + search(tr[x][cur], y + 1,  len);
		else{
			res = res + search(g[x], y, len);
		}
		return res;
	}
}trie1, trie2;

int n;
const int SIZE = 320;
void solve(){
	LL ans = 0;
	cin >> n;
	string line;
	getline(cin, line);
	trie1.init(); trie2.init();
	trie2.mark = 0;
	data.clear();
	for(int i = 1; i <= n; i ++){
		getline(cin, str);
		data.push_back(str);
		if(str[0] == '+'){
			trie2.add(1, 1, str.size() - 1);
			if(trie2.tot > SIZE){
				trie2.mark = str.size();
				trie1.init();
				trie1.flag = 0;
				for(int j = 0; j < trie2.mark; j ++){
					str = data[j];
					trie1.add(1, 1, str.size() - 1);
				}
				trie2.init();
			} 
		}
		else{
			if(!trie1.flag) trie1.bfs();
			if(!trie2.flag) trie2.bfs();
			int l = str.size() - 1;
			LL x = ans % l;
			//cout << "x" << x << endl;
			str = '?' + str.substr(str.size() - x) + str.substr(1, str.size() - x - 1);
			//cout << str << endl;
			printf("%lld\n", ans = trie1.search(1, 1, l) + trie2.search(1, 1, l));
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	int testcase;
	cin >> testcase;
	for(int i = 1; i <= testcase; i ++){
		printf("Case #%d:\n", i);
		solve();
	}
}
