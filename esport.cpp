#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define ci pair<char, int>
#define iii pair<int, pair<int, int> >
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
#define yuht int _; cin >> _; while(_--)
#define vt vector<int>
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
const int MAX = MASK(20);
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,m;
int a[N], b[N], f[MAX];
ci p[N];
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	cin >> m;
	FOR(i,1,m) cin >> p[i].fi >> p[i].se;
	sort(a+1,a+n+1, greater<int>());
	FOR(i,1,m) b[i]=a[i];
	memset(f, 0, sizeof f);
	FORD(mask, MASK(m)-1,0){
		int k=popp(mask);
		if(k==m) continue;
		int res=0;
		while(mask & MASK(res)) ++res;
		char x=p[k+1].fi; int y=p[k+1].se;
		if(x=='p') f[mask]=f[mask | MASK(res)] + (y==1 ? b[res+1] : -b[res+1]);
		else{
			if(y==1){
				int mt=-INF;
				REP(i,m) if(!(mask & MASK(i))) maximize(mt, f[mask | MASK(i)]);
				f[mask]=mt;
			}
			else{
				int mt=INF;
				REP(i,m) if(!(mask & MASK(i))) minimize(mt, f[mask | MASK(i)]);
				f[mask]=mt;
			}
		}
	}
	cout << f[0];
}
//100077958169269
//iloveMT




