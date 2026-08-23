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
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,m,d;
int a[N], b[N], t[N];
int f[N], dp[N];
deque<int> dq;
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n >> m >> d;
	FOR(i,1,m) cin >> a[i] >> b[i] >> t[i];
	FOR(i,1,m){
		int xx=(i==1 ? d*(t[i]-1) : d*(t[i]-t[i-1]));
		minimize(xx, n);
		dq.clear();
		int res=0;
		FOR(j,1,n){
			int tmp=min(n,j+xx);
			while(res<tmp){
				++res;
				while(!dq.empty() && f[dq.back()]<=f[res]) dq.pop_back();
				dq.pb(res);
			}
			int cur=max(1ll, j-xx);
			while(!dq.empty() && dq.front()<cur) dq.pop_front();
			dp[j]=f[dq.front()]+b[i]-abs(j-a[i]);
		}
		FOR(j,1,n) f[j]=dp[j];
	}
	int mt=-INF;
	FOR(i,1,n) maximize(mt, f[i]);
	cout <<mt;
}
//100077958169269
//iloveMT




