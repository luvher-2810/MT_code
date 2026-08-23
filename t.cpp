#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define iii pair<int, pair<int, int> >
#define All(X) X.begin(), X.end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define TASK ""
#define yuht int _; cin >> _; while(_--)
#define vt vector<int>
#define vii vector<ii>
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt")
//#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 1e9+7;
const int mod = 998244353;
const int N = 2e5+10;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
struct HASH{
	ull h1,h2; int idx;
	bool operator<(const HASH& o) const {
		if(h1!=o.h1) return  h1<o.h1;
		if(h2!=o.h2) return  h2<o.h2;
		return idx<o.idx;	
	}
};
int n,m;
int a[N], b[N];
ull H1[N], H2[N], preA[N],preB[N], xorA[N], xorB[N];
HASH hs[N];
//--------------------------------------------------
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n; FOR(i,1,n) cin >> a[i];
	cin >> m; FOR(i,1,m) cin >> b[i];
	FOR(i,1,2e5){
		H1[i]=rng64();
		H2[i]=rng64();
	}
	preA[0]=xorA[0]=0;
	FOR(i,1,n){
		preA[i]=preA[i-1]+H1[a[i]];
		xorA[i]=xorA[i-1]^H2[a[i]];
	}
	preB[0]=xorB[0]=0;
	FOR(i,1,m){
		preB[i]=preB[i-1]+H1[b[i]];
		xorB[i]=xorB[i-1]^H2[b[i]];
	}
	FORD(k,min(n,m),1){
		int sz=0;
		FOR(i,1,n-k+1) hs[sz++]={preA[i+k-1]-preA[i-1],xorA[i+k-1]^xorA[i-1],i};
		sort(hs,hs+sz);
		FOR(i,1,m-k+1){
			ull x1=preB[i+k-1]-preB[i-1], x2=xorB[i+k-1]^xorB[i-1];
			HASH res={x1,x2,0};
			auto it=lower_bound(hs,hs+sz,res,[](const HASH& x, const HASH& y){
				if(x.h1!=y.h1) return x.h1<y.h1;
				return x.h2<y.h2;
			});
			if(it!=hs+sz && it->h1 == x1 && it->h2 == x2){
				cout << k << " " << it->idx << " " << i;
				return 0;
			}
		}
	}
	cout << 0 <<" "<< -1 <<" "<< -1; 
}
//100077958169269
//iloveMT
//MT^^






