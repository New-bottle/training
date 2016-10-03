#include<cstdio>
#include<deque>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100100;

deque<int>have[100];
string s[N];
bool used[N];
char d;
int n;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> s[i];
		sum += s[i].length();
	}
	sum /= (n >> 1);
	cin >> d;
	/*
	for(int i = 33; i <= 126; i ++)
		cout << i << " " << (char)i << "!!" << endl;
		*/
	for(int i = 1; i <= n; i ++) s[i] += d;
	sort(s + 1, s + n + 1);

	for(int i = 1; i <= n; i ++)
		have[s[i].length() - 1].push_back(i);

	int now = 1;
	for(int i = 1; i <= (n >> 1) && now <= n; i ++) {
		while(used[now] && now <= n) now ++;
		if (now > n) break;
//		printf("now = %d\n", now);
		cout << s[now];
		used[now] = 1;
		int l = s[now].length() - 1;
		now ++;
		int t = have[sum - l].front();
		while(used[t]) {
			t = have[sum - l].front();
			have[sum - l].pop_front();
		}
		used[t] = 1;
//		have[sum - l].pop_front();
		s[t][s[t].length() - 1] = '\n';
		cout << s[t];
	}
	cout << flush;
	return 0;
}
