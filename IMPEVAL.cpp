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
#define f1(i,n) for(int i=1;i<=n;++i)
#define f0(i,n) for(int i=0;i<n;++i)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT "IMPEVAL"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
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
//----------------------MT---------------------------
int n,m,q;
vector<ii> g[N];
ii E[N];
int dist[3][N];
void djk(int rt){
	for(int i=1;i<=n;i++) dist[rt][i]=INF;
	priority_queue<ii, vector<ii>, greater<ii>> q;
	dist[rt][rt]=0;
	q.push({0,rt});
	while(!q.empty()){
		ii cur = q.top(); q.pop();
		int d=cur.fi, u=cur.se;
		if(d!=dist[rt][u]) continue;
		for(ii e : g[u]){
			int v=e.fi, w=e.se;
			if(dist[rt][v]>d+w){
				dist[rt][v]=d+w;
				q.push({dist[rt][v],v});
			}
		}
	}
}
struct node{
	ll x,y,u,id,rid;
	node() {}
	node(ll _x, ll _y, ll _u, ll _id, ll _rid)
		: x(_x), y(_y), u(_u), id(_id), rid(_rid){}
	bool operator<(const node &other) const {
		return x < other.x;
	}
};
vector<node> pnt, qr;
vt cmp;
int bit[N];
void add(int i, int val){
	for(;i<cmp.size()+5;i+=i&-i) bit[i]+=val;
}
int sum(int i){
	int res=0;
	for(;i>0;i-=i&-i) res+=bit[i];
	return res;
}
ii ans[N];
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> m >> q;
	for(int i=1;i<=n;i++) g[i].clear();
	pnt.clear();cmp.clear();qr.clear();
	memset(bit,0,sizeof bit);
	for(int i=1;i<=m;i++){
		int u,v,w; cin >> u >> v >> w;
		g[u].pb({v,w}); g[v].pb({u,w});
		E[i]={u,v};
	}
	djk(1);djk(2);
	for(int i=1;i<=n;i++){
		pnt.pb({dist[1][i],dist[2][i],i,-1,-1});
		cmp.pb(dist[2][i]);
	}
	for(int i=1;i<=q;i++){
		int id, nw;cin >> id >> nw;
		int u=E[id].fi, v=E[id].se;
		int nx=min(dist[1][u], dist[1][v]+nw), ny=min(dist[2][u], dist[2][v]+nw);
		qr.pb({nx,ny,u,i,id});
		cmp.pb(ny);
		nx=min(dist[1][v], dist[1][u]+nw), ny=min(dist[2][v], dist[2][u]+nw);
		qr.pb({nx,ny,v,i,id});
		cmp.pb(ny);
	}
	sort(pnt.begin(),pnt.end());
	sort(qr.begin(),qr.end());
	sort(cmp.begin(),cmp.end());
	cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
	int j=0;
	for(node it : qr){
		while(j<pnt.size() && pnt[j].x<=it.x){
			int pos=lower_bound(cmp.begin(),cmp.end(),pnt[j].y)-cmp.begin()+1;
			add(pos,1);
			j++;
		}
		int pos=lower_bound(cmp.begin(),cmp.end(),it.y)-cmp.begin()+1;
		int cur=sum(pos)+1;
		int u=it.u;
		if(ii(dist[1][u],dist[2][u])==ii(it.x,it.y)) cur--;
		if(u==E[it.rid].fi) ans[it.id].fi=cur;
		else ans[it.id].se=cur;
	}
	for(int i=1;i<=q;i++) cout << ans[i].fi<<" "<<ans[i].se<<el;
}
//100077958169269
//Toi yeu Minh Thuy


