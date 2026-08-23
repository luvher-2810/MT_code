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
#define MT "TET"
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
int a[N], p[N];
bool rev[N], xx[N];
struct MINHTHUYCUTENHATTHEGIOI{
	int par[N],len[N],sum[N];
	miti mp[N];
	void init(int n){
		for(int i=1;i<=n;i++){
			par[i]=i;
			len[i]=sum[i]=0;
			mp[i].clear();
		}
	}
	int find(int x){
		if(par[x]==x) return x;
		return par[x]=find(par[x]);
	}
	void unite(int u,int v){
		u=find(u),v=find(v);
		if(u==v) return;
		if(mp[u].size()<mp[v].size()) swap(u,v);
		int mt=0;
		for(auto it : mp[v]){
			int val=it.fi, cnt=it.se;
			auto jt=mp[u].find(val);
			if(jt!=mp[u].end()){
				mt+=jt->se*cnt;
				jt->se+=cnt;
			}
			else{
				mp[u][val]=cnt;
			}
		}
		sum[u]+=sum[v]+mt;
		len[u]+=len[v];
		par[v]=u;
		mp[v].clear();
	}
} dsu;
int mx=0;
int calc(int x){
	return 1+dsu.len[x]*(dsu.len[x]-1)/2 - dsu.sum[x];
}
void add(int pos){
	xx[pos]=true;
	dsu.par[pos]=pos;
	dsu.len[pos]=1;
	dsu.sum[pos]=0;
	dsu.mp[pos].clear();
	dsu.mp[pos][a[pos]]=1;
	maximize(mx,1ll);
	if(pos>1 && xx[pos-1]){
		dsu.unite(pos,pos-1);
		int r=dsu.find(pos), v=calc(r);
		maximize(mx,v);
	}
	if(pos<n && xx[pos+1]){
		dsu.unite(pos,pos+1);
		int r=dsu.find(pos), v=calc(r);
		maximize(mx,v);
	}
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=q;i++){
		cin >> p[i];
		rev[p[i]]=true;
	}
	dsu.init(n);
	for(int i=1;i<=n;i++) if(!rev[i]) add(i);
	int ans[q+5];
	ans[q]=mx;
	for(int i=q;i>=1;i--){
		add(p[i]);
		ans[i-1]=mx;
	}
	for(int i=1;i<=q;i++) cout << ans[i]<<el;
}
//100077958169269
//I love mthuyyyyyy
//You are lucy, I am luvher, we are a couple


