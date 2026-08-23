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
#define All(X) X.begin(), X.end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
#define yuht int _; cin >> _; while(_--)
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
const int MOD = 998244353;
//const int mod = 998244353;
const int N = 2e5+10;
const ll INF = 1e18;
const int LG = 20;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int mul(int a, int b){
	return(a%MOD*b%MOD)%MOD;
}
void add(int &a, int b){
	a+=b;
	if(a>=MOD) a-=MOD;
}
vt<int> calc(int x){
	vt<int> tmp;
	while(x){
		tmp.pb(x%10);
		x/=10;
	}
	return tmp;
}
int n;
int cnt[12], s[12][12];
int pw[N];
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n;
	FOR(i,1,n){
		int x; cin >> x;
		vt<int> k=calc(x);
		int xx=k.size();
		cnt[xx]++;
		FOR(i,1,xx) s[xx][i]+=k[i-1];
	}
	pw[0]=1;
	FOR(i,1,LG) pw[i]=mul(pw[i-1],10);
	int mt=0;
	FOR(x,1,10) FOR(k,1,10){
		FOR(i,1,x){
			int pos=(i<=k ? 2*(i-1)+1 : (i-1)+k);
			int cur=mul(pw[pos], mul(s[x][i], cnt[k]));
			add(mt, cur);
		}
		FOR(i,1,k){
			int pos=(i<=x ? 2*(i-1) : (i-1)+x);
			int cur=mul(pw[pos], mul(s[k][i], cnt[x]));
			add(mt, cur);
		}
	}
	cout << mt;
}
//100077958169269
//iloveMT




