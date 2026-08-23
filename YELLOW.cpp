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
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,q;
int a[N], nxt[N];
struct LCA{
	int up[LG][N];
	void build(){
		FOR(i,1,n) up[0][i]=nxt[i];
		FOR(k,1,LG-1) FOR(i,1,n) up[k][i]=up[k-1][up[k-1][i]];
	}
	int get(int l, int r, int x){
		int u=l;
		FORD(k,LG-1,0) {
			if(up[k][u]<=r && a[up[k][u]]>x) u=up[k][u];
		}
		return nxt[u];
	}
} lca;
void hnim(){
	int l,r,x; cin >> l >> r >> x;
	while(l<=r){
		if(a[l]>x){
			l=lca.get(l,r,x);
			if(l>r) break;
		}
		x%=a[l];
		l=nxt[l];
	}
	cout << x << el;
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n >> q;
	FOR(i,1,n) cin >> a[i];
	stack<int> st;
	FORD(i,n,1){
		while(!st.empty() && a[st.top()]>=a[i]) st.pop();
		if(!st.empty()) nxt[i]=st.top();
		else nxt[i]=n+1;
		st.push(i);
	}
	lca.build();
	while(q--) hnim();
}
//100077958169269
//iloveMT




