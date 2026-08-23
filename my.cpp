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
const int N = 1e6+10;
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N], f[N], pos[N];
bool ok(int x){
	FOR(i,1,n) f[i]=(pos[i] ? 0 : (i<=x ? 1 : -1));
	FORD(i,n,1){
		f[i]=(f[i]>0 ? 1 : (f[i]<0 ? -1 : 0));
		f[a[i]]+=f[i];
	}
	return f[1]>=0;
}
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n;
	FOR(i,2,n) cin >> a[i], pos[a[i]]=1;
	int l=1,r=n;
	while(l<r){
		int mid=(l+r)/2;
		if(ok(mid)) r=mid;
		else l=mid+1;
	}
	cout << l;
	
}
//100077958169269
//iloveMT



