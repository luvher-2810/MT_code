#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
#define el "\n"
#define miti pair<ll,ll>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt")
#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 1e9+7;
const int mod = 998244353;
const int N = 1e5+10;
const int MXE=12*N+5;
const ll INF = 9e18;
const int sf[9][2]={{0,0},{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
//----------------------MT---------------------------
struct dsu{
	int p[N], r[N];
	void init(int n){
		for(int i=1;i<=n;i++) p[i]=i,r[i]=0;
	}
	int find(int x){
		while(p[x]!=x) p[x]=p[p[x]], x=p[x];
		return x;
	}
	bool unite(int a, int b){
		a=find(a);b=find(b);
		if(a==b) return false;
		if(r[a]<r[b]) swap(a,b);
		p[b]=a;
		if(r[a]==r[b]) r[a]++;
		return true;
	}
};
struct edge{
	int u,v,w;
};
ll n,s,k;
ll X[N], Y[N], nxt[N], cmp[N];
edge E[MXE];
ll ecnt;
ll tx[N], ty[N],idx[N],key[N], pos[N], bit1[N], bit2[N];
void upd(int i, int v1,int v2, int k){
	for(;i<=k;i+=i&-i){
		if(v1<bit1[i]){
			bit1[i]=v1;
			bit2[i]=v2;
		}
	}
}
ii get(int i){
	ll mn=INF, mx=-1;
	for(;i>0;i-=i&-i){
		if(bit1[i]<mn){
			mn=bit1[i];
			mx=bit2[i];
		}
	}
	return {mn,mx};
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	#define MT "INTERNET"
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> s >> k;
	for(int i=1;i<=n;i++) cin >> X[i] >> Y[i];
	dsu pnt;
	pnt.init(n);
	if(s>=0){
		int cz=s+1;
		unordered_map<ull,int> he;
		he.reserve(n*2+10);
		for(int i=1;i<=n;i++) nxt[i]=0;
		auto kf=[&](int cx, int cy) ->ull{
			return ((ull)cx << 32) ^ ((ull)cy & 0xffffffffULL);
		};
		for(int i=1;i<=n;i++){
			ull ky=kf(X[i]/cz,Y[i]/cz);
			int prev=he.count(ky) ? he[ky] : 0;
			nxt[i]=prev;
			he[ky]=i;
		}
		for(int i=1;i<=n;i++){
			int cx=X[i]/cz, cy=Y[i]/cz;
			for(int t=0;t<9;t++){
				int cx1=cx+sf[t][0], cy1=cy+sf[t][1];
				ull kz=kf(cx1,cy1);
				if(!he.count(kz)) continue;
				int j=he[kz];
				for(;j!=0;j=nxt[j]){
					if(j<=i) continue;
					int dist=abs(X[i]-X[j])+abs(Y[i]-Y[j]);
					if(dist<=s) pnt.unite(i,j);
				}
			}
		}
	}
	unordered_map<int,int> cm;
	cm.reserve(n*2);
	int cn=0;
	for(int i=1;i<=n;i++){
		int r=pnt.find(i);
		if(!cm.count(r)) cm[r]=++cn;
		cmp[i]=cm[r];
	}
	if(k==0){
		cout << 0 << el;
		return 0;
	}
	ecnt=0;
	for(int rt=0;rt<4;rt++){
		if(rt==0) for(int i=1;i<=n;i++){
			tx[i]=X[i];ty[i]=Y[i];idx[i]=i;
		}
		else if(rt==1) for(int i=1;i<=n;i++){
			tx[i]=Y[i];ty[i]=X[i];idx[i]=i;
		}
		else if(rt==2) for(int i=1;i<=n;i++){
			tx[i]=-X[i];ty[i]=Y[i];idx[i]=i;
		}
		else for(int i=1;i<=n;i++){
			tx[i]=Y[i];ty[i]=-X[i];idx[i]=i;
		}
		sort(idx+1,idx+n+1,[&](int a,int b){
			if(tx[a]!=tx[b]) return tx[a]<tx[b];
			return ty[a]<ty[b];	
		});
		for(int i=1;i<=n;i++) key[i]=ty[idx[i]]-tx[idx[i]];
		sort(key+1, key+n+1);
		int xx = 1;
		for(int i = 2; i <= n; i++){
		    if(key[i] != key[xx]) key[++xx] = key[i];
		}
		for(int i=1;i<=n;i++){
			int kx=ty[idx[i]]-tx[idx[i]],ps=(ll)(lower_bound(key+1,key+xx+1,kx)-key);
			pos[i]=ps;
		}
		for(int i=1;i<=xx;i++) bit1[i]=INF, bit2[i]=-1;
		for(int i=n;i>=1;i--){
			int ix=idx[i], ps=pos[i], r=xx-ps+1;
			ii q=get(r);
			if(q.se!=-1){
				int ps1=q.se, ix1=idx[ps1];
				int w=abs(X[ix]-X[ix1])+abs(Y[ix]-Y[ix1]);
				if(ecnt+1<MXE){
					E[++ecnt].u=ix;E[ecnt].v=ix1;E[ecnt].w=w;
				}
			}
			int up=tx[ix]+ty[ix], ups=xx-ps+1;
			upd(ups,up,i,xx);
		}
	}
	if(ecnt==0){
		cout << 0 << el;
		return 0;
	}
	sort(E+1,E+ecnt+1,[&](const edge &a, const edge &b){
		if(a.w!=b.w) return a.w<b.w;
		if(a.u!=b.u) return a.u<b.u;
		return a.v<b.v;
	});
	dsu res;
	res.init(cn);
	int ad=0, ans=0;
	for(int i=1;i<=ecnt;i++){
		int u=E[i].u,v=E[i].v;
		int cu=cmp[u], cv=cmp[v];
		if(cu==cv) continue;
		if(res.unite(cu,cv)){
			ans+=E[i].w;
			ad++;
			if(ad==k) break;
		}
	}
	cout << ans;
}
//100077958169269
//Toi yeu Minh Thuy


