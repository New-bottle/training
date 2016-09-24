#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include<algorithm>

struct Missle {
	int arrive;
	int fly;
	int damage;
};

Missle hurt[24000];
int n, m;
int p;
int ttldmg;
int TA, TB, SA, SB;

struct Query {
	int l, r;
	int val;
};

std::vector<Query> qs;

const int N = 20010;
int v[N << 1], t[N << 2], ad[N << 2];

#define mid ((l + r) >> 1)
#define L (o << 1)
#define R (o << 1 | 1)
#define lch L, l, mid
#define rch R, mid + 1, r

void Push_up(int o) {
	t[o] = std::max(t[L], t[R]);
}
void Push_down(int o) {
	if (ad[o]) {
		t[L] += ad[o]; ad[L] += ad[o];
		t[R] += ad[o]; ad[R] += ad[o];
		ad[o] = 0;
	}
}
void update(int o, int l, int r, int ql, int qr, int v) {
	if (ql <= l && qr >= r){ 
		ad[o] += v; t[o] += v;
	} else {
		Push_down(o);
		if (ql <= mid) update(lch, ql, qr, v);
		if (qr >  mid) update(rch, ql, qr, v);
		Push_up(o);
	}
}

int yhy()
{
	using namespace std;
	memset(t, 0, sizeof t);
	memset(ad, 0, sizeof ad);
	int cnt = 0;
	for(int i = 0; i < qs.size(); i ++) {
		v[++ cnt] = qs[i].l;
		v[++ cnt] = qs[i].r;
	}
	sort(v + 1, v + cnt + 1);
	cnt = unique(v + 1, v + cnt + 1) - v - 1;
	for(int i = 0; i < qs.size(); i ++) {
		qs[i].l = lower_bound(v + 1, v + cnt + 1, qs[i].l) - v;
		qs[i].r = lower_bound(v + 1, v + cnt + 1, qs[i].r) - v;
	}
	for(int i = 0; i < qs.size(); i ++)
		update(1, 1, cnt, qs[i].l, qs[i].r, qs[i].val);
	return t[1];
}

void work()
{
	for (int i = 0; i < p; ++i) {
		Missle& mis = hurt[i];
		int bfirst = mis.arrive + mis.fly;
		if (bfirst < SB || bfirst > SB + TB) {
			// reject and bomb B immediately
			Query qr;
			qr.l = std::max(0, mis.arrive - TA);
			qr.r = mis.arrive;
			qr.val = mis.damage;
			qs.push_back(qr);
			continue;
		}
		int blast = bfirst + (SB + TB - bfirst) / (mis.fly * 2) * (mis.fly * 2);
		//std::cout << "BFIST " << bfirst << std::endl;
		//std::cout << "BLAST " << blast << std::endl;
		int alast = blast + mis.fly;
		int l = std::max(0, alast - TA);
		int r = mis.arrive;
		if (l <= r) {
			Query qr;
			qr.l = l;
			qr.r = r;
			qr.val = mis.damage;
			qs.push_back(qr);
		}
	}
	std::cout << ttldmg - yhy() << std::endl;
#if 0
	for (int i = 0; i < (int) qs.size(); ++i) {
		std::cout << qs[i].l << ' ' << qs[i].r << ' ' << qs[i].val << std::endl;
	}
#endif
}

int main()
{
	while (scanf("%d%d", &TA, &TB) == 2) {
		p = 0;
		ttldmg = 0;
		qs.clear();
		scanf("%d", &SB);
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			int launch, fly, damage;
			scanf("%d%d%d", &launch, &fly, &damage);
			int arriveb = launch + fly;
			if (arriveb >= SB && arriveb <= SB + TB) {
				hurt[p].arrive = arriveb + fly;
				hurt[p].fly = fly;
				hurt[p].damage = damage;
				++p;
				ttldmg += damage;
			}
		}
		for (int i = 0; i < m; ++i) {
			int launch, fly, damage;
			scanf("%d%d%d", &launch, &fly, &damage);
			int arrivea = launch + fly;
			hurt[p].arrive = arrivea;
			hurt[p].fly = fly;
			hurt[p].damage = damage;
			++p;
			ttldmg += damage;
		}
		//std::cout << ttldmg << std::endl;
		work();
	}
}
