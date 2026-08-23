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
#define TASK "paroti.uyt"
#define vt vector
#define el "\n"
#define miti priority_queue<ii, vt<ii>, greater<ii>>
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
const int N = 4000+10;
const ll INF = 1e18;
//--------------------------------------------------
struct Edge{
	int to,w;
};
struct Pix{
	int u,v,d;
};
bool cmp1(const Pix &a, const Pix &b){
	return a.d<b.d;
}
struct Query{
	int idx,d,s;
};
bool cmp2(const Query &a, const Query &b){
	return a.d<b.d;
}
int n,m,k;
vt<Edge> g[N];
int dist[N], par[N], sz[N];
int find(int x){
	if(par[x]==x) return x;
	return par[x]=find(par[x]);
}
void unite(int a, int b){
	a=find(a);b=find(b);
	if(a==b) return;
	if(sz[a]<sz[b]) swap(a,b);
	par[b]=a;
	sz[a]+=sz[b];
}
void solve(){
	cin >> n >> m >> k;
	FOR(i,1,n) g[i].clear();
	FOR(i,1,m){
		int u,v,w; cin >> u >> v >> w;
		g[u].pb({v,w});
		g[v].pb({u,w});
	}
	Query qr[k+5], st[k+5];
	FOR(i,1,k){
		cin >> qr[i].s >> qr[i].d;
		qr[i].idx=i;
		st[i]=qr[i];
	}
	vt<Pix> p;
	FOR(x,1,n){
		FOR(i,1,n) dist[i]=INF;
		miti q;
		dist[x]=0;
		q.push({0,x});
		while(!q.empty()){
			ii cur=q.top();q.pop();
			int d=cur.fi, u=cur.se;
			if(d!=dist[u]) continue;
			REP(i,g[u].size()){
				int v=g[u][i].to, wt=d+g[u][i].w;
				if(minimize(dist[v],wt)) q.push({wt,v});
			}
		}
		FOR(i,x+1,n) if(dist[i]<INF) p.pb({x,i,dist[i]});
	}
	sort(p.begin(), p.end(), cmp1);
	sort(st+1,st+k+1,cmp2);
	FOR(i,1,n) par[i]=i, sz[i]=1;
	int ans[k+5],pt=0;
	FOR(i,1,k){
		while(pt<p.size() && p[pt].d<=st[i].d){
			unite(p[pt].u, p[pt].v);
			++pt;
		}
		ans[st[i].idx]=sz[find(st[i].s)];
	}
	FOR(i,1,k) cout << ans[i]<<el;
}
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
}
//iloveMT
//luvher
//lucifer





