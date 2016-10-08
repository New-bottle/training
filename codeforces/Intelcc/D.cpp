#include<cstdio>
#include<set>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;

int n, m, ans[26];
char s1[N];
bool yes[N];
vector<int>have[26];
typedef pair<int,int> pii;
set<int> s;
set<int> ::iterator it;

int main() {
	scanf("%d", &m);
	scanf("%s", s1 + 1);
	n = strlen(s1 + 1);
	for(int i = 1; i <= n; i ++)
		have[s1[i] - 'a'].push_back(i);
	int nowr = 0, nowl, ed = 0;
	s.insert(0);
	s.insert(n + 1);
	for(int i = 0; i < 26; i ++) {
		for(int j = 0; j < have[i].size(); j ++) {
			it = s.lower_bound(have[i][j]);
			nowr = *it;
			it --;
			nowl = *it;
//			printf("nowl = %d nowr = %d\n", nowl, nowr);
			if (nowr - nowl <= m) continue;
			if (j + 1 < have[i].size() && have[i][j + 1] - nowl <= m)
				continue;
			yes[have[i][j]] = 1;
			ans[i] ++;
			s.insert(have[i][j]);
		}
		nowr = 0;
		bool sign = 1;
		for(it = s.begin(); it != s.end(); it ++) {
			if (*it > nowr + m) {
				sign = 0;
				break;
			} else {
				nowr = *it;
			}
		}
		if (sign) {
			ed = i;
			break;
		} else {
			for(int j = 0; j < have[i].size(); j ++)
				s.insert(have[i][j]);
		}
	}
	

	for(int i = 0; i < ed; i ++)
		for(int j = 0; j < have[i].size(); j ++) putchar(i + 'a');
	for(int j = 1; j <= ans[ed]; j ++) putchar(ed + 'a');
	puts("");
	return 0;
}
