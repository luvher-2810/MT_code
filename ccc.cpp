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
const int N = 2e5+10;
const int LG = 20;
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N], st[N][LG], lg[N];

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	FOR(i,2,n) lg[i]=lg[i/2]+1;
	FOR(i,1,n) st[i][0]=a[i];
	for(int j=1;MASK(j)<=n;j++){
		for(int i=1;i+MASK(j)-1<=n;i++){
			st[i][j]=min(st[i][j-1], st[i+MASK(j-1)][j-1]);
		}
	} 
	int q; cin >> q;
	while(q--){
		int l,r;  cin >> l >> r; 
		int k=lg[r-l+1];
		cout << min(st[l][k], st[r-MASK(k)+1][k])<<el;
	}
}
//100077958169269
//iloveMT



