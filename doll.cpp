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
#define TASK "DOLL"
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
const int N = 5e5+10;
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N];
int par[N], sz[N], res[N];
bool act[N];
int find(int x){
	if(x==par[x]) return x;
	else return par[x]=find(par[x]);
}
int calc(int x){
	return (x+1)/2;
}
int unite(int a, int b){
	a=find(a);b=find(b);
	if(a==b) return 0;
	if(sz[a]<sz[b]) swap(a,b);
	int x1=calc(sz[a])+calc(sz[b]);
	sz[a]+=sz[b];
	par[b]=a;
	return calc(sz[a])-x1;
}

//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	int mt=0;
	FOR(i,1,n){
		int x=a[i];
		if(!act[x]){
			act[x]=1;
			par[x]=x;
			sz[x]=1;
			mt+=1;
			if(x>1 && act[x-1]) mt+=unite(x,x-1);
			if(x+1<N && act[x+1]) mt+=unite(x,x+1);
		}
		res[i]=mt;
	}
	FOR(i,1,n) cout << res[i]<<" ";
}
//100077958169269
//iloveMT



