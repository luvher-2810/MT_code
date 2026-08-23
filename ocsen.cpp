#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define fi first
#define se second
#define mp make_pair
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
#define TASK "QSNAIL"
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
const int N = 5e5+10;
const int LG = 19;
const ll INF = 1e18;
//--------------------------------------------------
int up[N][LG], sum[N][LG];
int a[N], p[N];
vt<int> s;
int n,q;

//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin >> n >> q;
	FOR(i,1,n){
		char c; cin >> c;
		p[i]=p[i-1];
		if(c=='1'){
			++p[i];
			s.pb(i);
		}
	}
	FOR(i,1,n) cin >> a[i], a[i]+=a[i-1];
	REP(i,s.size()){
		vt<ii> v;
		FOR(j,s[i],(i == s.size()-1 ? n : s[i+1]-1)) v.pb({a[j],j});
		sort(v.begin(),v.end());
		FOR(j,(i==0 ? 1 : s[i-1]+1),s[i]){
			auto it=lower_bound(v.begin(),v.end(),mp(a[j-1],0ll));
			if(it!=v.end()){
				up[j][0]=it->se+1;
				sum[j][0]=1;
			}
			else up[j][0]=v[0].se+1;
		}
	}
	FOR(j,1,LG-1) FOR(i,1,n){
		up[i][j]=up[up[i][j-1]][j-1];
		sum[i][j]=sum[i][j-1]+sum[up[i][j-1]][j-1];
	}
	while(q--){
		int l,r; cin >> l >> r;
		int k=p[r]-p[l-1]-1, mt=0;
		for(int i=0;MASK(i)<=k;i++) if(BIT(k,i) && up[l][i] && up[l][i]-1<=r){
			mt+=sum[l][i];
			l=up[l][i];
		}
		cout << mt+(a[r]-a[l-1]>=0) << el;
	}
	
}
//100077958169269
//iloveMT



