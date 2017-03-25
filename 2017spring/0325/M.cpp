#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;

int n;
int fa[N], mp[N][N];
bool used[N];

int getnew()
{
	for (int i = 1; i <= n; ++i)
		if (!used[i]) return i;
	return -1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	int x, y;
	x = getnew();
	used[x] = 1;
	y = getnew();
	used[y] = 1;
	char ans[5];
	while (true) {
		if (x == -1 || y == -1) break;
		cout << "? " << x << ' ' << y << endl;
		cin >> ans;
		if (ans[0] == '<') {
			mp[x][y] = -1;
			mp[y][x] = 1;
			used[x] = used[y] = 1;
			y = getnew();
		} else if (ans[0] == '>') {
			mp[x][y] = 1;
			mp[y][x] = -1;
			used[x] = used[y] = 1;
			x = getnew();
		} else if (ans[0] == '=') {
			used[x] = used[y] = 1;
			y = getnew();
		}
	}
	if (x != -1) cout << "! " << x << endl;
else cout << "! " << y << endl;
	return 0;
}
