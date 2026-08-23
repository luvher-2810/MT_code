#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 3e5+2;
int n,q;
vector<pair<int,int>> adj[8*maxn];
int act1[maxn], act2[maxn], dist[8*maxn];
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> q;
	int cnt=n;
	for(int i=1;i<=n;i++) act1[i]=++cnt,act2[i]=++cnt;
	for(int i=1;i<=n;i++){
		int x; cin >> x;
		adj[i].push_back({act1[x],0});
		adj[act2[x]].push_back({i,0});
	}
	for(int i=1;i<=q;i++){
		int type, x,y; cin >> type >> x >> y;
		if(type==1){
			adj[act1[x]].push_back({act2[y],1});
			if(x!=y) adj[act1[y]].push_back({act2[x],1});
		}
		else{
			if(x==y) continue;
			int x1=++cnt, x2=++cnt;
			adj[act1[y]].push_back({x1,0});
			adj[act1[x]].push_back({x1,0});
			adj[x2].push_back({act2[y],0});
			adj[x2].push_back({act2[x],0});
			act1[y]=x1;
			act2[y]=x2;
			act1[x]=++cnt;
			act2[x]=++cnt;
		}
	}
	fill(dist, dist+cnt, -1);
	deque<int> q;
	q.push_back(1);
	dist[1]=0;
	while(!q.empty()){
		int u=q.front();q.pop_front();
		for(pair<int,int> it : adj[u]){
			int v=it.first, w=it.second;
			if(dist[v]==-1 || dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				if(w==0) q.push_front(v);
				else q.push_back(v);
			}
		}
	}
	for(int i=1;i<=n;i++) cout << dist[i]<<" ";
	
	
	return 0;
}
//luv


