#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define mint __int128
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
const ll INF = MASK(62);
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
struct Line{
	int x,y;
	int f(int z){
		return z*x+y;
	}
};
struct CHT{
	deque<Line> dq;
	bool calc(Line a, Line b, Line c){
		return (mint)(c.y-a.y)*(a.x-b.x)<=(mint)(b.y-a.y)*(a.x-c.x);
	}
	void add(int a, int b){
		Line res={a,b};
		while(dq.size()>=2 && calc(dq[dq.size()-2], dq.back(), res)) dq.pop_back();
		dq.pb(res);
	}
	int get(int n){
		while(dq.size()>=2 && dq[0].f(n)>=dq[1].f(n)) dq.pop_front();
		return dq[0].f(n);
	}
	void clr(){
		dq.clear();
	}
} convex;
int n,k;
int a[N], pre[N], f[N], dp[N];

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n >> k;
	FOR(i,1,n){
		cin >> a[i];
		pre[i]=pre[i-1]+a[i];
	}
	memset(f, 0x3f, sizeof f);
	f[0]=0;
	FOR(i,1,k){
		FOR(j,0,n) dp[j]=INF;
		convex.clr();
		convex.add(-2*pre[i-1], f[i-1]+pre[i-1]*pre[i-1]);
		FOR(j,i,n){
			dp[j]=pre[j]*pre[j]+convex.get(pre[j]);
			if(j<n && f[j]<INF) convex.add(-2*pre[j], f[j]+pre[j]*pre[j]);
		}
		FOR(j,0,n) f[j]=dp[j];
	}
	cout << f[n];
}
//100077958169269
//iloveMT
//MT^^





