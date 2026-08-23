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
#define vt vector
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
//--------------------------------------------------
int n,m,s;
vt<ii> adj[N];
int d[N];
void djk(int s){
	FOR(i,1,n) d[i]=INF;
	priority_queue<ii, vt<ii> , greater<ii> > q;
	d[s]=0;
	q.push({0,s});
	while(!q.empty()){
		ii xx=q.top();q.pop();
		int u=xx.se, du=xx.fi;
		if(du!=d[u]) continue;
		for(ii it : adj[u]){
			int v=it.fi, w=it.se;
			if(d[u]+w<d[v]){
				d[v]=d[u]+w;
				q.push({d[v],v});
			}
		}
	}
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> m >> s;
	FOR(i,1,m){
		int x,y,w; cin >> x >> y >> w;
		adj[x].pb({y,w});
		adj[y].pb({x,w});
	}
	djk(s);
	FOR(i,1,n){
		if(d[i]==INF) cout << -1;
		else cout << d[i];
		cout <<" ";
	}
}
//100077958169269
//iloveMT



