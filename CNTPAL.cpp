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
#define TASK "CNTPAL"
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
const int N = 5005;
const ll INF = 1e18;
//--------------------------------------------------
string s;
int n,q;
bool p[N][N];
int f[N][N];
//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin >> s;
	n=s.size();
	s=" "+s;
	FOR(i,1,n) p[i][i]=1;
	FOR(i,1,n-1) if(s[i]==s[i+1]) p[i][i+1]=1;
	FOR(k,3,n) FOR(i,1,n-k+1){
		int j=i+k-1;
		if(s[i]==s[j] && p[i+1][j-1]) p[i][j]=1;
	}
	FORD(i,n,1) FOR(j,i,n){
		if(i==j) f[i][j]=1;
		else f[i][j]=f[i+1][j]+f[i][j-1]-f[i+1][j-1]+p[i][j];
	}
	cin >> q;
	while(q--){
		int l,r; cin >> l >> r;
		cout << f[l][r]<<el;
	}
}
//100077958169269
//iloveMT



