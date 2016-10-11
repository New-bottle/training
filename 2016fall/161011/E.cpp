#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#define N 10010
#define eps 1e-6
#define PI acos(-1.0)
using namespace std;
int n;
double sqr(double x){
	return x * x;
}
struct Point{
	double x, y;
	friend double dist (const Point &a, const Point &b){
		return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
	}
}p[N];
double r[N];
double b[N];
double sign(double x){
	return x < -eps ? -1 : fabs(x) > eps;
}

double check(double x){
	r[1] = x;
	double res = x * x;
	for(int i = 1; i < n; i ++){
		r[i + 1] = b[i] - r[i];
		if(sign(r[i + 1]) < 0) return 1e30;
		res = res + r[i + 1] * r[i + 1];
	}
	if(r[1] + r[n] != b[n]) return 1e30;
	return res;
}

void solve(){
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	
	if(n & 1){
		double res = 0;
		for(int i = 1; i <= n; i ++){
			int p1 = (i - 1 + n) % n;
			int p2 = i % n;
			b[i] = dist(p[p1], p[p2]);
			if(i != n) res = b[i] - res;
		}
		r[n] = (res + b[n]) / 2;
		r[1] = (b[n] - res) / 2;
		
		for(int i = n - 1; i >= 2; i --){
			r[i] = b[i] - r[i + 1];
		}
	
		double ans = 0;
		for(int i = 1; i <= n; i ++){
			if(sign(r[i]) < 0){
				puts("IMPOSSIBLE");
				return;
			}
			ans = ans + r[i] * r[i];
		}
		printf("%.2f\n", ans * PI);
		for(int i = 1; i <= n; i ++){
			printf("%.2f\n", r[i]);
		}
	}
	else{
		for(int i = 1; i <= n; i ++){
			int p1 = (i - 1 + n) % n;
			int p2 = i % n;
			b[i] = dist(p[p1], p[p2]);
		}
		
		double l = 0, r = b[1];
		while(r - l > eps){
			double le = (l + l + r) / 3;
			double ri = (l + r + r) / 3;
			if(check(le) > check(ri)){
				l = le;
			}
			else{
				r = ri;
			}
		}
		
		double ans = check((l + r) / 2) * PI;
		if(ans > 1e29){
			puts("IMPOSSIBLE");
		}
		else{
			printf("%.2f\n", ans);
			for(int i = 1; i <= n; i ++){
				printf("%.2f\n", ::r[i]);
			}
		}
	}
}
int main(){
	int testcase;
	scanf("%d", &testcase);
	while(testcase --){
		solve();
	}
	
}
