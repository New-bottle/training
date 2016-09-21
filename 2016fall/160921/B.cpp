#include <cctype>
#include <iostream>
#include <string>

typedef long long lli;

std::string s;
int n;
int p;
lli xma;

lli getmul()
{
	lli ans = 1;
	while (1) {
		ans *= s[p] - '0';
		++p;
		if (p == n || s[p] != '*')
			break;
		++p;
	}
	if (p != n)
		++p;
	return ans;
}

lli evalexpr()
{
	p = 0;
	lli ans = 0;
	while (p != n)
		ans += getmul();
	return ans;
}

lli sumup()
{
	lli ans = s[0] - '0';
	bool nextadd = false;
	for (int i = 1; i < (int) s.size(); ++i) {
		char ch = s[i];
		if (std::isdigit(ch)) {
			if (nextadd)
				ans += ch - '0';
			else
				ans *= ch - '0';
		} else {
			nextadd = ch == '+';
		}
	}
	return ans;
}

void work()
{
	lli pri = evalexpr();
	lli lr = sumup();
	if (pri == xma && lr == xma) {
		std::cout << "U" << std::endl;
	} else if (pri == xma) {
		std::cout << "M" << std::endl;
	} else if (lr == xma) {
		std::cout << "L" << std::endl;
	} else {
		std::cout << "I" << std::endl;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	while (std::cin >> s >> xma) {
		n = s.size();
		work();
	}
	return 0;
}
