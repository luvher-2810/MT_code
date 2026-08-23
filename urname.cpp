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
const int N = 1e5+10;
const int LG=20;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,m;
int x[N], y[N];
int par[N], up[LG][N], depth[N];
int hull(int a, int b, int c){
	int x1=x[b]-x[a];
	int y1=y[b]-y[a];
	int x2=x[c]-x[a];
	int y2=y[c]-y[a];
	return x1*y2-y1*x2;
}
struct LCA{
	void build(){
		FOR(i,1,n) up[0][i]=par[i];
		FOR(i,1,LG-1) FOR(j,1,n){
			up[i][j]=up[i-1][up[i-1][j]];
		}
		FORD(i,n,1) depth[i]=depth[par[i]]+1;
	}
	int get(int u,int v){
		if(depth[u]<depth[v]) swap(u,v);
		FORD(i,LG-1,0){
			if(BIT(depth[u]-depth[v], i))
				u=up[i][u];
		}
		if(u==v) return u;
		FORD(i,LG-1,0){
			if(up[i][u]!=up[i][v]){
				u=up[i][u];
				v=up[i][v];
			}
		}
		return up[0][u];
	}
} lca;
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n;
	FOR(i,1,n) cin >> x[i] >> y[i];
	deque<int> q;
	FORD(i,n,1){
		while(q.size()>=2 && hull(i,q[0], q[1])>0) q.pop_front();
		if(q.empty()) par[i]=i;
		else par[i]=q.front();
		q.push_front(i);
	}
	lca.build();
	cin >> m;
	while(m--){
		int a,b; cin >> a >> b;
		cout << lca.get(a,b)<<el;
	}
}
//100077958169269
//iloveMT




