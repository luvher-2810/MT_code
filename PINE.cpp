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
#define MT "PINE"
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
int n,q;
int a[N],he[N],par[N],dth[N],hv[N],sz[N],pos[N],inv[N];
int to[N*2],nxt[2*N],hn[N],te,e;
struct BIT{
	int n,bit[N];
	void init(int _n){
		n = _n;
		for(int i=1;i<=n;i++) bit[i]=0;
	}
	void add(int i, int v){
		for(;i<=n;i+=i&-i) bit[i]+=v;
	}
	int sum(int i){
		int res=0;
		for(;i>0;i-=i&-i) res+=bit[i];
		return res;
	}
	int get(int l, int r){
		if(l>r) return 0;
		return sum(r)-sum(l-1);
	}
} bit1,bit2;
void ae(int u, int v){
	to[++e]=v;
	nxt[e]=hn[u];
	hn[u]=e;
}
int dfs(int u, int p){
	par[u]=p;
	sz[u]=1;
	int mx=0;
	hv[u]=0;
	for(int i=hn[u];i;i=nxt[i]){
		int v=to[i];
		if(v==p) continue;
		dth[v]=dth[u]+1;
		int cur=dfs(v,u);
		sz[u]+=cur;
		if(cur>mx){
			mx=cur;
			hv[u]=v;
		}
	}
	return sz[u];
}
void dec(int u, int h){
	he[u]=h;
	pos[u]=++te;
	inv[te]=u;
	if(hv[u]) dec(hv[u],h);
	for(int i=hn[u];i;i=nxt[i]){
		int v=to[i];
		if(v==par[u] || v==hv[u]) continue;
		dec(v,v);
	}
}
struct IT{
	int sx[4*N];
	void build(int id, int l, int r){
		if(l==r){
			sx[id]=a[inv[l]];
			return;
		}
		int mid=(l+r)/2;
		build(id*2,l,mid);
		build(id*2+1,mid+1,r);
		sx[id]=max(sx[id*2],sx[id*2+1]);
	}
	void ram(int id, int l, int r, int u, int v, int val){
		if(l>v || r<u || sx[id]<val) return;
		if(l==r){
			int t1=sx[id], t2=t1%val;
			if(t1!=t2){
				sx[id]=t2;
				bit1.add(t1+1,-1);bit1.add(t2+1,1);
				bit2.add(t1+1,-t1);bit2.add(t2+1,t2);
			}
			return;
		}
		int mid=(l+r)/2;
		ram(id*2,l,mid,u,v,val);
		ram(id*2+1,mid+1,r,u,v,val);
		sx[id]=max(sx[id*2],sx[id*2+1]);
	}
} st;
void upd(int u, int v, int w){
	while(he[u]!=he[v]){
		if(dth[he[u]]<dth[he[v]]) swap(u,v);
		st.ram(1,1,n,pos[he[u]],pos[u],w);
		u=par[he[u]];
	}
	if(dth[u]>dth[v]) swap(u,v);
	st.ram(1,1,n,pos[u],pos[v],w);
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<n;i++){
		int x,y; cin >> x >> y;
		ae(x,y);ae(y,x);
	}
	dfs(1,0);dec(1,1);
	bit1.init(N), bit2.init(N);
	for(int i=1;i<=n;i++){
		bit1.add(a[i]+1,1);
		bit2.add(a[i]+1,a[i]);
	}
	st.build(1,1,n);
	for(int t=1;t<=q;t++){
		int x,y,w; cin >> x >> y >> w;
		upd(x,y,w);
		int thufy=0;
		for(int i=0;i*t<=N;i++){
			int l=i*t, r=min(N-1,(i+1)*t-1);
			int s=bit2.get(l+1,r+1), c=bit1.get(l+1,r+1);
			thufy+=s-i*t*c;
		}
		cout << thufy<<el;
	}
}
//100077958169269
//I love mthuyyyyyy
//You are lucy, I am luvher, we are a couple



