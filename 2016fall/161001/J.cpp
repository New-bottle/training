#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#define LL long long
using namespace std;
LL a, b, c, d, p, m;
LL gcd(LL a, LL b){
	LL c;
	while(b){
		c = a;
		a = b;
		b = c % b;
	}
	return a;
}

struct Point{
	LL x, y;
	Point(){}
	Point(LL _x, LL _y){
		x = _x;
		y = _y;
	}
	friend bool operator < (const Point &a, const Point &b){
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
	friend bool operator == (const Point &a, const Point &b){
		return a.x == b.x && a.y == b.y;
	}
	bool in_rec(LL a, LL b, LL c, LL d){
		return (a <= x && x <= c && b <= y && y <= d);
	}
};

LL tmpx, tmpy;
LL lx, rx, midx, ly, ry, midy;
LL numx1, numx2, numy1, numy2;
LL add(Point a, Point b){
	if(a.in_rec(0, 0, midx, midy) && b.in_rec(0, 0, midx, midy)) return numx1 * numy1;
	if(a.in_rec(0, midy, midx, ry) && b.in_rec(0, midy, midx, ry)) return numx1 * numy2;
	if(a.in_rec(midx, 0, rx, midy) && b.in_rec(midx, 0, rx,midy)) return numx2 * numy1;
	if(a.in_rec(midx, midy, rx, ry) && b.in_rec(midx, midy, rx, ry)) return numx2 * numy2;
}
LL add(Point a){
	if(a.in_rec(0, 0, midx, midy)) return numx1 * numy1;
	if(a.in_rec(0, midy + 1, midx, ry)) return numx1 * numy2;
	if(a.in_rec(midx + 1, 0, rx, midy)) return numx2 * numy1;
	if(a.in_rec(midx + 1, midy + 1, rx, ry)) return numx2 * numy2;
}

LL solve(LL x, LL y){
	if(x < 0 || y < 0) return 0;
	lx = 0, rx = min(p - 1, x), midx = (x + 1) % p - 1; // 0 ~ x
	ly = 0, ry = min(p - 1, y), midy = (y + 1) % p - 1; // 0 ~ y
	numx1 = (x + 1) / p + ((x + 1) % p != 0), numx2 = (x + 1) / p;
	numy1 = (y + 1) / p + ((y + 1) % p != 0), numy2 = (y + 1) / p;
	/*
	cout << lx << ' ' << midx << ' ' << rx << endl;
	cout << numx1 << ' ' << numx2 << endl;
	cout << ly << ' ' << midy << ' ' << ry << endl;
	cout << numy1 << ' ' << numy2 << endl;
	cout << endl;
	*/
	vector<Point> list;
	list.clear();
	LL listx[] = {lx, midx, rx};
	LL listy[] = {ly, midy, ry};
	LL ans = 0;
	
	// x + y = m
	for(int i = 0; i < 3; i ++){
		Point tmp = Point(listx[i], m - listx[i]);
		if(tmp.in_rec(0, 0, rx, ry)){
			list.push_back(tmp);
		}
	}
	for(int i = 0; i < 3; i ++){
		Point tmp = Point(m - listy[i], listy[i]);
		if(tmp.in_rec(0, 0, rx, ry)){
			list.push_back(tmp);
		}
	}
	sort(list.begin(), list.end());
	int sz = unique(list.begin(), list.end()) - list.begin();
	for(int i = 0; i < sz; i ++){
		ans = ans + add(list[i]);
	}
	for(int i = 0; i < sz - 1; i ++){
		ans = ans + max(0LL, abs(list[i + 1].x - list[i].x - 1)) * add(list[i], list[i + 1]);
	}
	
	//x + y = m + p
	list.clear();
	for(int i = 0; i < 3; i ++){
		Point tmp = Point(listx[i], m + p - listx[i]);
		if(tmp.in_rec(0, 0, rx, ry)){
			list.push_back(tmp);
		}
	}
	for(int i = 0; i < 3; i ++){
		Point tmp = Point(m + p - listy[i], listy[i]);
		if(tmp. in_rec(0, 0, rx, ry)){
			list.push_back(tmp);
		}
	}
	sort(list.begin(), list.end());
	sz = unique(list.begin(), list.end()) - list.begin();
	for(int i = 0; i < sz; i ++){
		ans = ans + add(list[i]);
	}
	
	for(int i = 0; i < sz - 1; i ++){
		ans = ans + max(0LL, list[i + 1].x - list[i].x - 1) * add(list[i], list[i + 1]);
	}
	
	//cout << ans << endl;
	return ans;
}

int main(){
	int testcase;
	scanf("%d", &testcase);
	for(int i = 1; i <= testcase; i ++){
		scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &p, &m);
		LL son = solve(b, d) - solve(a - 1, d) -  solve(b, c - 1) + solve(a - 1, c - 1);
		LL mother = (b - a + 1) * (d - c + 1);
		LL g = gcd(son, mother);
		m = m % p;
		printf("Case #%d: %lld/%lld\n", i, son / g, mother / g);
	}
}
