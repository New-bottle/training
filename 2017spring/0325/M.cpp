#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n;
int t[N << 2], l[N << 2], r[N << 2];

#define L (o << 1)
#define R (o << 1 | 1)
#define mid ((l + r) >> 1)
char s[10];
void ask(int o, int l, int r)
{
	if (l == r) t[o] = l;
	else {
		ask(L, l, mid);
		ask(R, mid + 1, r);
		cout << "? " << t[L] << ' ' << t[R] << endl;
		cin >> s;
		if (s[0] == '<') t[o] = t[R];
		else t[o] = t[L];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	ask(1, 1, n);
//	cout << "!!!" << endl;
	int ans = 0;
	int l = 1, r = n, o = 1;
	if (t[R] == t[o]) {
		ans = t[L];
		o = R;
		l = mid + 1;
	} else {
		ans = t[R];
		o = L;
		r = mid;
	}
	while (l < r) {
		if (t[R] == t[o]) {
			cout << "? " << ans << ' ' << t[L] << endl;
			cin >> s;
			if (s[0] == '<') ans = t[L];
			o = R;
			l = mid + 1;
		} else {
			cout << "? " << ans << ' ' << t[R] << endl;
			cin >> s;
			if (s[0] == '<') ans = t[R];
			o = L;
			r = mid;
		}
	}
	cout << "! " << ans << endl;
	return 0;
}
