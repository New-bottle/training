#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define magic 0.916297857297023

int main()
{
	int x1, x2, y1, y2;
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	printf("%.15f\n", magic * ((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)));
	return 0;
}
