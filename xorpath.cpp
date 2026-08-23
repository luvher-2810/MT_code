#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
int n,q;
vector<pair<int,int>> adj[maxn];
int dist[maxn];
ll C[(1<<20)+5],ans[(1<<20)+5];
void dfs(int u, int p, int x){
	dist[u]=x;
	C[x]++;
	for(pair<int,int> it : adj[u]){
		int v=it.first, w=it.second;
		if(v!=p) dfs(v,u,x^w);
	}
}
void FFT(){
	for(int len=1;len*2<=(1<<20);len<<=1){
		for(int i=0;i<(1<<20);i+=2*len){
			for(int j=0;j<len;j++){
				ll u=C[i+j], v=C[i+len+j];
				C[i+j]=u+v;
				C[i+len+j]=u-v;
			}
		}
	}
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n-1;i++){
		int u,v,w; cin >> u >> v >> w;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	dfs(1,0,0); FFT();
	for(int i=0;i<(1<<20);i++) C[i]=C[i]*C[i];
	FFT();
	for(int i=0;i<(1<<20);i++) C[i]/=(1<<20);
	ans[0]=(C[0]-n)/2;
	for(int i=1;i<(1<<20);i++) ans[i] = (C[i]/2);
	cin >> q;
	while(q--){
		int x; cin >> x;
		if(x>=0 && x<(1<<20)) cout << ans[x]<<"\n";
		else cout << 0 <<"\n";
	}
	return 0;
}
//luv


