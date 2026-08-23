#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define prio priority_queue<ll, vector<ll>, greater<ll> > 
#define All(X) X.begin(),X.end()
#define task ""
const int MOD = 1e9+7;
const int maxn = 2e5+10;
const int LG = 20;
const ll INF = 1e18;
int n;
int a[maxn], tar[maxn];
vector<int> adj[maxn], V[maxn], vt[maxn];
int up[maxn][LG], depth[maxn], tin[maxn], TIMER;
void dfs(int u, int p, int x){
	tin[u]=++TIMER;
	up[u][0]=(p==-1 ? u : p);
	for(int i=1;i<LG;i++) up[u][i]=up[up[u][i-1]][i-1];
	depth[u]=x;
	for(int v : adj[u]) if(v!=p) dfs(v,u,x+1);
}
int lca(int u, int v){
	if(depth[v]>depth[u]) swap(u,v);
	int dif=depth[u]-depth[v];
	for(int i=0;i<LG;i++) if((dif>>i)&1) u=up[u][i];
	if(u==v) return u;
	for(int i=LG-1;i>=0;i--) if(up[u][i]!=up[v][i]){
		u=up[u][i];
		v=up[v][i];
	}
	return up[u][0];
}
int get(int u, int v){
	return depth[u]+depth[v]-depth[lca(u,v)]*2;
}
bool cmp(int a, int b){return tin[a]<tin[b];}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	int t; cin >> t;
//	build();
	while(t--){
		cin >> n; int ans[n+5];
		for(int i=1;i<=n;i++){
			V[i].clear();
			adj[i].clear();
			vt[i].clear();
			ans[i]=-1;
		}
		for(int i=1;i<=n;i++){
			cin >> a[i];
			V[a[i]].push_back(i);
		}
		for(int i=1;i<=n;i++) cin >> tar[i];
		for(int i=1;i<=n-1;i++){
			int x,y; cin >> x>> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		TIMER=0;
		dfs(1,-1,0);
		for(int k=1;k<=n;k++){
			if(V[k].empty()) continue;
			vector<int> A=V[k];
			sort(All(A),cmp);
			int _A=A.size();
			for(int i=0;i<_A-1;i++) A.push_back(lca(A[i],A[i+1]));
			sort(All(A),cmp);
			A.erase(unique(All(A)), A.end());
			for(int x : A) vt[x].clear();
			for(int i=1;i<A.size();i++){
				int x=lca(A[i-1],A[i]);
				vt[x].push_back(A[i]);
				vt[A[i]].push_back(x);
			}
			int centroid=-1, mn=INF;
			function<int(int,int)> dfs1=[&](int u, int p) -> int {
				int sz=(a[u]==k ? 1 : 0), mx=-INF;
				for(int v : vt[u]){
					if(v==p) continue;
					int xx=dfs1(v,u);
					sz+=xx;
					mx=max(mx,xx);
				}
				mx=max(mx,(int)V[k].size()-sz);
				if(mx<mn){
					mn=mx;
					centroid=u;
				}
				return sz;
			};
			dfs1(A[0],-1);
			int sum=0;
			for(int x : V[k]) sum+=get(centroid, x);
			vector<pair<int,int>> edge;
			function<int(int,int)> dfs2=[&](int u, int p) -> int {
				int sz=(a[u]==k ? 1 : 0), mx=-INF;
				for(int v : vt[u]){
					if(v==p) continue;
					int xx=dfs2(v,u);
					sz+=xx;
					edge.push_back({xx,get(u,v)});
				}
				return sz;
			};
			dfs2(centroid, -1);
			sort(All(edge)); reverse(All(edge));
			int res=tar[k]-1;
			for(pair<int,int> x : edge){
				int v=x.first, w=x.second,xx=min(res,w);
				sum-=xx*v;
				res-=xx;
				if(res==0) break;
			}
			ans[k]=sum;
		}
		for(int i=1;i<=n;i++) cout << ans[i]<<" ";
		cout <<"\n";
	}
	return 0;
}
//luv


