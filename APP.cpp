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
#define vt vector<int>
#define el "\n"
#define miti map<ll,ll>
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
int par[N], sz[N];
miti cnt[N];
int a[N];
int n,q;
int find(int x){
	if(x==par[x]) return x;
	else return par[x]=find(par[x]);
}
void unite(int a, int b){
	a=find(a);b=find(b);
	if(a==b) return ;
	if(sz[a]<sz[b]) swap(a,b);
	par[b]=a;
	sz[a]+=sz[b];
	if(cnt[a].size()<cnt[b].size()) swap(cnt[a],cnt[b]);
	for(ii it : cnt[b]) cnt[a][it.fi]+=it.se;
	cnt[b].clear();
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> q;
	FOR(i,1,n){
		cin >> a[i];
		par[i]=i;
		sz[i]=1;
		cnt[i][a[i]]=1;
	}
	while(q--){
		int t,x,y; cin >> t >> x >> y;
		if(t==1) unite(x,y);
		else{
			int u=find(x);
			if(cnt[u].count(y)) cout << cnt[u][y]<<el;
			else cout << 0<<el;
		}
	}
	
}
//100077958169269
//iloveMT



