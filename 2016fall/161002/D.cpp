#include<cstdio>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	int dist1 = a * a + b * b;
	int dist2 = c * c;
	if(dist1 > dist2) puts("Impossible");
	else if(dist1 == dist2) puts("Single staircase");
	else{
		long double d1 = sqrt((long double) dist1);
		long double d2 = c;
		long double d3 = d2 - d1;
		long double x = a / d1 * (d1 + d3 / 2);
		long double y = b / d1 * (d1 + d3 / 2);
		long double z = d3 / 2;
		std::cout << std::fixed << std::setprecision(12) << x << ' ';
		std::cout << std::fixed << std::setprecision(12) << y << ' ';
		std::cout << std::fixed << std::setprecision(12) << z << '\n';
	}

}
