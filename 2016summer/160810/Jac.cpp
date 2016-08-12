#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;

int n, m;
char ss[3][N];
char ans[N];
int cnt[3], all;

void modify( int i, int delta ) {
	if( ss[0][i]==ss[1][i] && ss[0][i]==ss[2][i] ) {
		return;
	} else if( ss[0][i]==ss[1][i] ) {
		cnt[2] += delta;
	} else if( ss[0][i]==ss[2][i] ) {
		cnt[1] += delta;
	} else if( ss[1][i]==ss[2][i] ) {
		cnt[0] += delta;
	} else {
		all += delta;
	}
}
bool check( int a, int b, int c ) {
	if( a<0 || b<0 || c<0 ) return false;
	a -= all;
	b -= all;
	c -= all;
	for( int i=0; i<3; i++ ) {
		int r[3];
		r[0]=a, r[1]=b, r[2]=c;
		for( int j=0; j<3; j++ ) {
			if( i==j ) continue;
			r[j] -= cnt[j];
		}
		int vmin = 0x3f3f3f3f;
		for( int j=0; j<3; j++ ) {
			if( i==j ) continue;
			vmin = min( vmin, r[j] );
		}
		vmin = min( vmin, cnt[i] );
		vmin = max( vmin, 0 );
		for( int j=0; j<3; j++ ) {
			if( i==j ) {
				r[j] -= cnt[i]-vmin;
			} else {
				r[j] -= vmin;
			}
		}
		int tp = all;
		for( int j=0; j<3; j++ ) {
			if( r[j]<0 )
				tp -= -r[j];
		}
		if( tp >= 0 ) return true;
	}
	return false;
}
int main() {
	freopen("J.in","r",stdin);
	freopen("J.ans","w",stdout);
	while(1) {
		scanf( "%d%d", &n, &m );
		if( n==0 && m==0 ) return 0;
		for( int i=0; i<3; i++ )
			scanf( "%s", ss[i]+1 );
		cnt[0] = cnt[1] = cnt[2] = all = 0;
		for( int i=n; i>=1; i-- ) 
			modify( i, +1 );
		if( !check(m,m,m) ) {
			printf( "-1\n" );
		} else {
			int a=m, b=m, c=m;
			for( int i=1; i<=n; i++ ) {
				vector<char> vc(1,'A');
				for( int j=0; j<3; j++ )
					vc.push_back( ss[j][i] );
				sort( vc.begin(), vc.end() );
				modify( i, -1 );
				for( int t=0; t<4; t++ ) {
					int aa = a - (ss[0][i]!=vc[t]);
					int bb = b - (ss[1][i]!=vc[t]);
					int cc = c - (ss[2][i]!=vc[t]);
					if( check(aa,bb,cc) ) {
						a = aa;
						b = bb;
						c = cc;
						ans[i] = vc[t];
						break;
					}
				}
			}
			ans[n+1] = 0;
			printf( "%s\n", ans+1 );
		}
	}
}
