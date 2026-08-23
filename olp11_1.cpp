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
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT ""
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
const int N = 4e5+10;
const int LG = 20;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,m,t,k;
int h[N],to[N*2], nxt[N*2], wt[N*2],ec;
int on[N], d[N];
struct Node {
	int d,u;
	bool operator<(Node const &other) const {
		return d>other.d;
	}
};
int eu[N*2], ev[N*2], ew[N*2], ce[N*2], ca[N*2], cb[N*2],cc;
int par[N], mh[N],mn[N*2], mz[N*2],mw[N*2], mc;
int up[LG][N],mx[LG][N], dth[N];
int find(int x){
	return par[x]==x ? x : par[x]=find(par[x]);
}
void unite(int a, int b){
	a=find(a), b=find(b);
	if(a!=b) par[b]=a;
}
void add(int u, int v, int w){
	to[++ec]=v;
	wt[ec]=w;
	nxt[ec]=h[u];
	h[u]=ec;
}
void mst(int u, int v, int w){
	mn[++mc]=v;
	mw[mc]=w;
	mz[mc]=mh[u];
	mh[u]=mc;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	cin >> n >> m >> k >> t;
	f1(i,m) {
		int u,v,w; cin >> u >> v >> w;
		add(u,v,w);add(v,u,w);
		eu[i]=u;ev[i]=v;ew[i]=w;
	}
	priority_queue<Node> q;
	f1(i,n) d[i]=INF,on[i]=-1;
	f1(i,k) {
		dth[i]=-1;
		par[i]=i;
		d[i]=0;
		on[i]=i;
		q.push({0,i});
	}
	while(!q.empty()){
		Node cur = q.top(); q.pop();
		if(cur.d!=d[cur.u]) continue;
		int u=cur.u;
		for(int e=h[u];e;e=nxt[e]){
			int v=to[e],w=wt[e];
			if(minimize(d[v],d[u]+w)){
				on[v]=on[u];
				q.push({d[v],v});
			}
		}
	}
	f1(i,m) {
		int u=eu[i], v=ev[i];
		if(on[u]!=on[v]){
			ce[++cc]=d[u]+ew[i]+d[v];
			ca[cc]=on[u];cb[cc]=on[v];
		}
	}
	vt xx(cc);
	f1(i,cc) xx[i-1]=i;
	sort(xx.begin(),xx.end(),[&](int a,int b){
		return ce[a]<ce[b];
	});
	int us=0;
	f0(i,xx.size()) {
		int ix=xx[i],a=ca[ix], b=cb[ix];
		if(find(a)!=find(b)){
			unite(a,b);
			mst(a,b,ce[ix]);
			mst(b,a,ce[ix]);
			us++;
			if(us==k-1) break;
		}
	}
	f1(s,k) {
		if(dth[s]!=-1) continue;
		dth[s]=up[0][s]=mx[0][s]=0;
		queue<int> qq;
		qq.push(s);
		while(!qq.empty()){
			int u=qq.front();qq.pop();
			for(int e=mh[u];e;e=mz[e]){
				int v=mn[e];
				if(dth[v]==-1){
					dth[v]=dth[u]+1;
					up[0][v]=u;
					mx[0][v]=mw[e];
					qq.push(v);
				}
			}
		}
	}
	f1(i,LG-1) f1(j,k) {
		up[i][j]=up[i-1][up[i-1][j]];
		mx[i][j]=max(mx[i-1][j], mx[i-1][up[i-1][j]]);
	}

	while(t--){
		int a,b; cin >> a >> b;
		int mt=0;
		if(dth[a]<dth[b]) swap(a,b);
		int dif=dth[a]-dth[b];
		f0(i,LG) if(dif & MASK(i)) {
			maximize(mt,mx[i][a]);
			a=up[i][a];
		}
		if(a!=b){
			for(int i=LG-1;i>=0;i--){
				if(up[i][a]!=up[i][b]){
					maximize(mt,max(mx[i][a],mx[i][b]));
					a=up[i][a];b=up[i][b];
				}
			}
			maximize(mt,max(mx[0][a],mx[0][b]));
		}
		cout << mt << el;
	}
}
//I love mthuyyyyyy
//You are lucy, I am luvher, we are a couple




