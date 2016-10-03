#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 110
using namespace std;
int n;
char str[N][N];
vector< pair<int, int> > data1, data2, data3;
bool vis1[N], vis2[N];

pair<int, int> calc(char *str){
	int len = strlen(str);
	
	int l = 0, r = 0;
	for(int i = 0; i < len; i ++){
		if(str[i] == '(') l ++;
		else{
			if(l) l --;
			else r ++;
		}
	}
	return make_pair(l, r);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%s", str[i] + 1);
		pair<int, int> tmp = calc(str[i] + 1);
		if(tmp.first > tmp.second) data1.push_back(tmp);
		else if(tmp.first == tmp.second) data2.push_back(tmp);
		else data3.push_back(tmp);
	}
	
	int sz = data1.size();
	int cur_left = 0;
	
	for(int i = 0; i < sz; i ++){
		bool flag = 0;
		for(int j = 0; j < sz; j ++){	
			if(!vis1[j] && cur_left >= data1[j].second){
				vis1[j] = 1;
				cur_left = cur_left - data1[j].second + data1[j].first;
				flag = 1;
				break;
			}
		}
		if(!flag){
			puts("No");
			return 0;
		}
	}
	
	sz = data2.size();
	for(int i = 0; i < sz; i ++){
		if(data2[i].second > cur_left){
			puts("No");
			return 0;
		}
	}
	
	sz = data3.size();
	int cur_right = 0;
	for(int i = 0; i < sz; i ++){
		bool flag = 0;
		for(int j = 0; j < sz; j ++){	
			if(!vis2[j] && cur_right >= data3[j].first){
				flag = 1;
				vis2[j] = 1;
				cur_right = cur_right - data3[j].first + data3[j].second;
				break;
			}
		}
		if(!flag){
			puts("No");
			return 0;
		}
	}
	
	if(cur_left == cur_right){
		puts("Yes");
	}
	else{
		puts("No");
	}
}
