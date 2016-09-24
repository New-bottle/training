#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const long double PI = acos((long double)-1);
const int N = 800010;
typedef long long LL;
#define double long double
#define int long long

struct comp {
	double r, i;
	comp(double r0 = 0.0, double i0 = 0.0):r(r0), i(i0){}
	friend comp operator + (const comp &a, const comp &b) {
		return comp(a.r + b.r, a.i + b.i);
	}
	friend comp operator - (const comp &a, const comp &b) {
		return comp(a.r - b.r, a.i - b.i);
	}
	friend comp operator * (const comp &a, const comp &b) {
		return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
	}
} number1[N], number2[N], number[N];

LL answer[N];

int length;
inline int lowbit(int x){ return x & (-x); }
void FFT(comp number[], int length, int type) {
	for(int i = 1, j = 0; i < length - 1; i ++) {
		for(int k = length; j ^= k >>= 1, ~j & k; );
		if (i < j) swap(number[i], number[j]);
	}
	comp unit_p0;
	for(int turn = 0; (1 << turn) < length; turn ++) {
		int step = 1 << turn, step2 = step << 1;
		double p0 = PI / step * type;
		//sincos(p0, &unit_p0.i, &(double)unit_p0.r);
		unit_p0.i = sin(p0);
		unit_p0.r = cos(p0);
		for(int i = 0; i < length; i += step2) {
			comp unit = 1;
			for(int j = 0; j < step; j ++) {
				comp &number1 = number[i + j + step];
				comp &number2 = number[i + j];
				comp delta = unit * number1;
				number1 = number2 - delta;
				number2 = number2 + delta;
				unit = unit * unit_p0;
			}
		}
	}
}

int len;
void multiply() {
	for(length = len; lowbit(length) != length; length ++);
//	for(length = 1; length / 2 < len; length <<= 1);
	FFT(number1, length, 1);
	FFT(number2, length, 1);
	for(int i = 0; i < length; i ++)
		number[i] = number1[i] * number2[i];
	FFT(number, length, -1);
	for(int i = 0; i < length; i ++)
		answer[i] = (LL)(number[i].r / length + 0.5);
}

LL a[N], b[N];
int n;

void work() {
	memset(number1, 0, sizeof number1);
	memset(number2, 0, sizeof number2);
	memset(number, 0, sizeof number);
	memset(answer, 0, sizeof answer);
	for(int i = 0; i < n; i ++) number1[i + n].r = number1[i].r = a[i];
	number1[n * 2 - 1].r = 0;

	reverse(number1, number1 + n * 2 - 1);

	for(int i = 0; i < n; i ++) number2[i].r = b[i];
	for(int i = 0; i < n; i ++) number2[i + n].r = 0;

	len = 2 * n - 1;
	multiply();
	LL mx = -1e18, sum = 0;
	for(int i = 0; i < n; i ++)
		sum += 1LL * a[i] * a[i] + 1LL * b[i] * b[i];
	for(int i = 2 * n - 2; i > n - 2; i --)
		mx = max(answer[i], mx);
	cout << sum - mx * 2 << endl;
//	printf("%lld\n", sum - mx * 2);
}

signed main(){
	int cs;
	scanf("%lld", &cs);
	while(cs --) {
		scanf("%lld", &n);
		for(int i = 0; i < n; i ++) scanf("%lld", &a[i]);
		for(int i = 0; i < n; i ++) scanf("%lld", &b[i]);
		work();
	}
	return 0;
}
