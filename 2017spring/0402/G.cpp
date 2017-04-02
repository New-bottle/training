#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 110;
const int P = 1e9 + 7;
int n, m, k;
struct Matrix
{
	int a[N][N];
	Matrix (int x = 0)
	{
		memset(a, 0, sizeof a);
		for (int i = 0; i < n; ++i) a[i][i] = x;
	}
	int* operator [] (int x) {return a[x];}
	int const* operator [] (int x) const {return a[x];}
	Matrix operator * (const Matrix &b) const {
		Matrix c;
		for (int i = 0; i < n; ++i)
			for (int k = 0; k < n; ++k)
				for (int j = 0; j < n; ++j)
					c[i][j] = int(((LL)c[i][j] + (LL)a[i][k] * b[k][j]) % (LL)P);
		return c;
	}
}a;
struct matrix
{
	int a[N][N];
	matrix (int x = 0)
	{
		memset(a, 0, sizeof a);
		for (int i = 0; i < n; ++i) a[i][i] = x;
	}
	int* operator [] (int x) {return a[x];}
	int const* operator [] (int x) const {return a[x];}
	matrix operator * (const matrix &b) const {
		matrix c;
		for (int i = 0; i < n; ++i)
			for (int k = 0; k < n; ++k)
				for (int j = 0; j < n; ++j)
					c[i][j] |= a[i][k] & b[k][j];
		return c;
	}
}p;

matrix Pow(matrix a, int b)
{
	matrix r(1);
	while (b)
	{
		if (b & 1) r = r * a;
		a = a * a;
		b >>= 1;
	}
	return r;
}
Matrix Pow(Matrix a, int b)
{
	Matrix r(1);
	while (b)
	{
		if (b & 1) r = r * a;
		a = a * a;
		b >>= 1;
	}
	return r;
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		--x; --y;
		a[x][y] += 1;
		a[y][x] += 1;
		p[x][y] = p[y][x] = 1;
	}
	Matrix b = Pow(a, k);
	matrix c = Pow(p, k);
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (c[i - 1][j - 1]) printf("%d", b[i - 1][j - 1]);
			else printf("%d", -1);
			printf("%c", j == n ? '\n' : ' ');
		}
	}
	return 0;
}
