#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define N 60
using namespace std;
char str[N];
int n;
struct node{
	char f[N];
	int len;
	node(){len = 0;}
	friend bool operator < (const node &a, const node &b){
		if(a.len != b.len) return a.len < b.len;
		for(int i = 1; i <= a.len; i ++){
			if(a.f[i] != b.f[i]) return a.f[i] < b.f[i];
		}
		return false;
	}
	void print(){
		f[len + 1] = 0;
		puts(f + 1);
	}
}dp[N][N];

pair<bool, node> solve(int a, int b){
	int len = b - a + 1;
	if(dp[a][b].len != -1) return make_pair(dp[a][b].len, dp[a][b]);
	node &res = dp[a][b];
	res.len = 0;
	if(len < 6){
		for(int i = a; i <= b; i ++){
			if(!isdigit(str[i]) && str[i] != '?'){
				return make_pair(0, res);
			}
			if(str[i] == '0' && i == a && len > 1) return make_pair(0, res);
		}
		for(int i = a; i <= b; i ++){
			if(!isdigit(str[i])) res.f[i - a + 1] = '9';
			else res.f[i - a + 1] = str[i];
		}
		res.len = len;
		return make_pair(1, res);
	}
	
	bool flag = 1;
	for(int i = a; i <= b; i ++){
		if(!isdigit(str[i]) && str[i]  != '?' || str[i] == '0' && i == a){
			flag = 0;
			break;
		}
	}
	if(flag){
		for(int i = a; i <= b; i ++){
			if(!isdigit(str[i])){
				res.f[i - a + 1] = '9';
			}	
			else res.f[i - a + 1] = str[i]; 
		}
		res.len = len;
		//return make_pair(1, res);
	}
	if((str[a + 1] != '(' && str[a + 1] != '?' || str[b] != ')' && str[b] != '?') || (str[a] != 'R' && str[a] != 'L' && str[a] != '?'));
	else{
		for(int i = a + 3; i <= b - 2; i ++)if (str[i] == '?' || str[i] == ','){
			pair<bool, node> l = solve(a + 2, i - 1);
			pair<bool, node> r= solve(i + 1, b - 1);
			if(l.first && r.first){
				flag = 1;
				res = (str[a] == '?') ? max(res, max(l.second, r.second)) : (str[a] == 'L' ? max(res, l.second) : max(res, r.second));
			}	
		}
	}
	return make_pair(flag, res);
}
int main(){
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++) dp[i][j].len = -1;
	}
	pair<bool, node> ans = solve(1, n);
	if(ans.first == 0){
		puts("invalid");
	}
	else{
		ans.second.print();
	}
	return 0;
}
