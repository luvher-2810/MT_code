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
const int N = 1e6+10;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,k;
int a[N], cnt[N], pre[N];

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n >> k;
	int mx=0;
	FOR(i,1,n) {
		cin >> a[i];
		maximize(mx, a[i]);
		cnt[a[i]]++;
	}
	FOR(i,1,mx) pre[i]=pre[i-1]+cnt[i];
	int mt=0;
	FOR(i,1,mx){
		int len=min(k+1,i), s=0;
		for(int j=i;j<=mx;j+=i){
			int x=min(mx, j+len-1);
			s+=pre[x]-pre[j-1];
			if(s==n) break;
		}
		if(s==n) mt=i;
	}
	cout << mt;
	
}
//100077958169269
//iloveMT




