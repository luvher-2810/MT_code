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
#define yuht int _; cin >> _; while(_--)
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
void hnim(){
	int n; cin >> n;
	int a[n+5];
	bool ok=true;
	int mn=INF;
	FOR(i,1,n){
		cin >> a[i];
		if(i>1 && a[i]<a[i-1]) ok=false;
		minimize(mn,a[i]);
	}
	if(ok){
		cout <<"YES"<<el;
		return;
	}
	int l=INF, r=-INF;
	FOR(i,1,n) if((a[i]&1)!=(mn&1)){
		minimize(l,a[i]);
		maximize(r,a[i]);
	}
	if(l==INF){
		cout << "NO"<<el;
		return;
	}
	int x1=0,x2=n+1;
	bool check=false;
	FOR(i,1,n){
		if((a[i]&1)==(mn&1) && a[i]<l) x1=i;
		if((a[i]&1)==(mn&1) && a[i]>r && !check){
			x2=i;
			check=true;
		}
	}
	cout <<(x1>x2 ? "NO" : "YES")<<el;
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	yuht hnim();
}
//100077958169269
//iloveMT




