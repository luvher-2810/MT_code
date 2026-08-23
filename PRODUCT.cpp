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
#define TASK "PRODUCT"
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
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N];
//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	int mt=0, cnt=0, mn=INF;
	FOR(i,1,n){
		int x1=abs(a[i]-1), x2=abs(a[i]+1);
		if(x1<=x2){
			mt+=x1;
			minimize(mn,x2-x1);
		}
		else{
			mt+=x2;
			++cnt;
			minimize(mn,x1-x2);
		}
	}
	cout <<(cnt%2 ? mt+mn : mt);
}
//100077958169269
//iloveMT



