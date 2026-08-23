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
#define TASK "MAZE"
#define vt vector
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
const int N =1e4+10;
const ll INF = 1e18;
//--------------------------------------------------
int n,m,q;
string a[105], b[105];
int cmp[16][N];
struct EDGE{
	int u,v,c;
};
vt<EDGE> edge;
vt<int> msk;
struct DSU{
	int par[N];
	int find(int x){
		if(par[x]==x) return x;
		return par[x]=find(par[x]);
	}
	void unite(int a, int b){
		a=find(a);
		b=find(b);
		if(a!=b) par[b]=a;
	}
};
int calc(char x){
	if(x=='P') return 1;
	if(x=='C') return 2;
	if(x=='N') return 4;
	if(x=='Z') return 8;
	return 0;
}
bool cp(int a, int b){
	int x=popp(a), y=popp(b);
	return x!=y ? x<y : a<b;
}
//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin >> n >> m;
	FOR(i,1,n) cin >> a[i];
	FOR(i,1,n-1) cin >> b[i];
	FOR(i,1,n) FOR(j,1,m-1) edge.pb({(i-1)*m+j,(i-1)*m+j+1, calc(a[i][j-1])});
	FOR(i,1,n-1) FOR(j,1,m) edge.pb({(i-1)*m+j, i*m+j, calc(b[i][j-1])});
	FOR(mask,1,15){
		DSU d;
		FOR(i,1,n*m) d.par[i]=i;
		for(EDGE it : edge) if((it.c&(~mask))==0) d.unite(it.u,it.v);
		FOR(i,1,n*m) cmp[mask][i]=d.find(i);
	}
	FOR(i,1,15) msk.pb(i);
	sort(msk.begin(),msk.end(),cp);
	cin >> q;
	while(q--){
		int a,b,c,d; cin >> a >> b >> c >> d;
		int u=(a-1)*m+b, v=(c-1)*m+d;
		if(u==v){
			cout << 0 << el;
			continue;
		}
		int mt=4;
		for(int it : msk) if(cmp[it][u]==cmp[it][v]){
			mt=popp(it);
			break;
		}
		cout << mt << el;
	}
}
//100077958169269
//iloveMT



