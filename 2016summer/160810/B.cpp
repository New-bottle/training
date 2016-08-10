#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

typedef long double ldb;

struct Card {
	int suit;
	int v;
	bool operator < (const Card& r) const {
		return v < r.v;
	}
	bool operator > (const Card& r) const {
		return r < *this;
	}
};

char fuck[][10] = {
		"UNKNOWN",
		"HIGHCARD",
		"PAIR",
		"TWOPAIR",
		"THREE",
		"STRAIT",
		"FLUSH",
		"HOUSE",
		"FOUR",
		"SFLUSH"
};

struct Hand {
	Card a[5];
	enum Kind {
		UNKNOWN = 0,
		HIGHCARD,
		PAIR,
		TWOPAIR,
		THREE,
		STRAIT,
		FLUSH,
		HOUSE,
		FOUR,
		SFLUSH,
	} k;
	void eval() {
		rearr();
#if 0
		for (int i = 0; i < 5; ++i) {
			std::cout << a[i].suit << ',' << a[i].v << '\t';
		}
		std::cout << std::endl;
#endif

		if (a[1].v == a[2].v + 1 &&
				a[2].v == a[3].v + 1 &&
				a[3].v == a[4].v + 1 &&
				(a[0].v == a[1].v + 1 ||
				(a[0].v == 12 && a[4].v == 0))
			) {
			// straight
			if (isflush)
				k = SFLUSH;
			else
				k = STRAIT;
			if (a[0].v == 12 && a[4].v == 0)
				a[0].v = 0;
			return;
		}
		if (a[0].v == a[3].v) {
			k = FOUR;
			return;
		}
		if (a[0].v == a[2].v && a[3].v == a[4].v) {
			k = HOUSE;
			return;
		}
		if (isflush) {
			k = FLUSH;
			return;
		}
		if (a[0].v == a[2].v) {
			k = THREE;
			return;
		}
		if (a[0].v == a[1].v) {
			if (a[2].v == a[3].v)
				k = TWOPAIR;
			else
				k = PAIR;
			return;
		}
		k = HIGHCARD;
	}
	bool isflush;
	void rvs() {
		std::reverse(a, a + 5);
	}
	void rearr() {
		std::sort(a, a + 5);

		if (a[0].suit == a[1].suit &&
				a[0].suit == a[2].suit &&
				a[0].suit == a[3].suit &&
				a[0].suit == a[4].suit)
			isflush = true;
		else
			isflush = false;

		int spos = 0;
		std::set<std::pair<int, int> ,std::greater<std::pair<int, int> > > s;
		for (int i = 1; i < 5; ++i) {
			if (a[i].v != a[i - 1].v) {
				s.insert(std::make_pair(i - spos, a[i - 1].v));
				spos = i;
			}
		}
		s.insert(std::make_pair(5 - spos, a[4].v));
		int c = 0;
		for (auto& p : s) {
			for (int i = 0; i < p.first; ++i) {
				a[c++].v = p.second;
			}
		}
#if 0
		std::sort(a, a + 5, std::greater<Card>());
		if (a[0].v == a[1].v) { // pair
			if (a[1].v == a[2].v)
				return; // 3
			if (a[2].v == a[3].v && a[3].v == a[4].v) {
				rvs();
				return;
			}
			if (a[2].v == a[3].v) // 4 or 2pair
				return;
			if (a[3].v == a[4].v) { // 2pair
				Card tmp = a[2];
				a[2] = a[3];
				a[3] = a[4];
				a[4] = tmp;
			}
			return;
		} else if (a[2].v == a[3].v && a[3].v == a[4].v) { // 4 or 3
			rvs();
			if (a[2].v != a[3].v && a[3].v < a[4].v) // 3
				std::swap(a[3], a[4]);
		} else if (a[1].v == a[2].v && a[2].v == a[3].v) { // 3
			Card tmp = a[0];
			for (int i = 0; i < 3; ++i)
				a[i] = a[i + 1];
			a[3] = tmp;
		} else if (a[1].v == a[2].v && a[3].v == a[4].v) { // 2pair
			Card tmp = a[0];
			a[0] = a[1];
			a[1] = a[2];
			a[2] = a[3];
			a[3] = a[4];
			a[4] = tmp;
		} else { // pair
			for (int i = 2; i < 5; ++i) {
				if (a[i].v == a[i - 1].v) {
					Card tmp = a[i - 1];
					Card tnp = a[i];
					for (int j = 2; j <= i; ++j)
						a[j] = a[j - 2];
					a[0] = tmp;
					a[1] = tnp;
					break;
				}
			}
		}
#endif
	}
	int cps() {
		int ans = 0;
		for (int i = 0; i < 5; ++i)
			ans = ans * 16 + a[i].v;
		return ans;
	}
	bool operator < (const Hand& rhs) const {
		if (k < rhs.k)
			return true;
		else if (k > rhs.k)
			return false;
		for (int i = 0; i < 5; ++i) {
			if (a[i] < rhs.a[i])
				return true;
			else if (a[i] > rhs.a[i])
				return false;
		}
		return false;
	}
};

//Hand mem[400000];
Hand Mmine, Mfoe, Mmax;
Card hset[7];
Card chosen[6];
Card mine[2], foe[2];

char buf[7][3];

int usedv[13];
bool usedc[13][4];

inline void adduse(const Card& c)
{
	++usedv[c.v];
	usedc[c.v][c.suit] = true;
}

inline void unuse(const Card& c)
{
	--usedv[c.v];
	usedc[c.v][c.suit] = false;
}

inline Card ch2v(const char *s)
{
	Card ans;
	ans.suit = s[0] == 'S' ? 0 : s[0] == 'H' ? 1 : s[0] == 'D' ? 2 : 3;
	char ch = s[1];
	if (std::isdigit(ch))
		ans.v = ch - '0' - 2;
	else if (ch == 'A')
		ans.v = 12;
	else if (ch == 'J')
		ans.v = 9;
	else if (ch == 'Q')
		ans.v = 10;
	else if (ch == 'K')
		ans.v = 11;
	else if (ch == 'T')
		ans.v = 8;
	return ans;
}

void clearall()
{
	std::memset(usedv, 0, sizeof(usedv));
	std::memset(usedc, 0, sizeof(usedc));
}

void parseinput()
{
	mine[0] = ch2v(buf[0]); adduse(mine[0]);
	mine[1] = ch2v(buf[1]); adduse(mine[1]);
	foe [0] = ch2v(buf[2]); adduse(foe [0]);
	foe [1] = ch2v(buf[3]); adduse(foe [1]);
	hset[0] = ch2v(buf[4]); adduse(hset[0]);
	hset[1] = ch2v(buf[5]); adduse(hset[1]);
	hset[2] = ch2v(buf[6]); adduse(hset[2]);
}

void Mflush()
{
	Hand hand;
	std::memcpy(hand.a, chosen, sizeof (hand.a));
	hand.eval();
	Mmax = std::max(Mmax, hand);
}

void bforce(int cur, int ch)
{
	// TODO: optimize
	if (cur == 7) {
		if (ch == 5) {
#if 0
			for (int i = 0; i < 5; ++i) {
				std::cout << chosen[i].v << ' ';
			}
				std::cout << std::endl;
#endif
			Mflush();
		}
		return;
	}
	if (ch > 5)
		return;
	chosen[ch] = hset[cur];
	bforce(cur + 1, ch + 1);
	bforce(cur + 1, ch);
}

void clearmm()
{
	std::memset(Mmax.a, 0, sizeof(Mmax.a));
	Mmax.k = Hand::UNKNOWN;
}

ldb work()
{
	int wins = 0;
	int ttl = 0;
	for (int i = 0; i < 13; ++i) {
	for (int ii = 0; ii < 4; ++ii) {
		if (usedc[i][ii])
			continue;
		Card c1;
		c1.v = i;
		c1.suit = ii;
		adduse(c1);
		hset[3] = c1;
		for (int j = 0; j < 13; ++j) {
		for (int jj = 0; jj < 4; ++jj) {
			if (usedc[j][jj] || j < i || (j == i && jj < ii))
				continue;
			Card c2;
			c2.v = j;
			c2.suit = jj;
			adduse(c2);
			hset[4] = c2;

			hset[5] = mine[0];
			hset[6] = mine[1];

#if 0
			for (int i = 0; i < 7; ++i) {
				std::cout << hset[i].v << ' ';
			}
			std::cout << std::endl;
#endif
			clearmm();
			bforce(0, 0);
			Mmine = Mmax;

			hset[5] = foe [0];
			hset[6] = foe [1];
			clearmm();
			bforce(0, 0);
			Mfoe  = Mmax;

			if (Mfoe < Mmine) {
#if 0
				std::sort(Mmine.a, Mmine.a + 5);
				std::sort(Mfoe.a, Mfoe.a + 5);
				for (int i = 0; i < 5; ++i) {
					std::cout << Mmine.a[i].v + 2 << " \t"[i == 4];
				}
				for (int i = 0; i < 5; ++i) {
					std::cout << Mfoe.a[i].v + 2 << ' ';
				}
				std::cout << std::endl;
#endif
				++wins;
			}
			++ttl;

			unuse(c2);
		}}
		unuse(c1);
	}}
	//std::cout << ttl << std::endl;
	return (ldb) wins / ttl;
}

#if 0
int main()
{
	while (~scanf("%s%s%s%s%s", buf[0], buf[1], buf[2], buf[3], buf[4])) {
		Hand hand;
	hand.a[0] = ch2v(buf[0]); adduse(hand.a[0]);
	hand.a[1] = ch2v(buf[1]); adduse(hand.a[1]);
	hand.a[2] = ch2v(buf[2]); adduse(hand.a[2]);
	hand.a[3] = ch2v(buf[3]); adduse(hand.a[3]);
	hand.a[4] = ch2v(buf[4]); adduse(hand.a[4]);
	hand.eval();
	std::cout << fuck[hand.k] << ' ' << hand.a[0].v << ' ' << hand.a[4].v << std::endl;;

	}
}
#endif

//#if 0
int main()
{
	while (scanf("%s%s%s%s%s%s%s", buf[0], buf[1], buf[2], buf[3], buf[4],
			buf[5], buf[6]) == 7 && buf[0][0] != '#') {
		clearall();
		parseinput();
		ldb ans = work();
		double bns = ans;
		printf("%.10lf\n", bns);
	}
	return 0;
}
//#endif
