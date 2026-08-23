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
#define vii vector<ii>
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt")
#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 998244353;
const int mod = 998244353;
const int N = 505;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int C[N], X[N][N], f[N][N];
void hnim(){
	int n; cin >> n;
	int a[n+5];
	memset(X, 0,sizeof X);
	FOR(i,1,n){
		cin >> a[i];
		X[i][i] = (a[i]==0 || a[i]==-1) ? 1 : 0;
	}
	FOR(i,1,n){
		FOR(j,1,i) FOR(k,1,i-j+1) f[j][k]=0;
		FORD(j,i,1){
			f[j][1]=(f[j][1]+X[j][i]);
			FOR(k,j,i-1){
				if(!X[j][k]) continue;
				int *f1=f[j], *f2=f[k+1];
				FOR(t,1,i-k) f1[t+1]=(f1[t+1]+X[j][k]*f2[t])%MOD;
			}
			FOR(t,1,i-j+1) f[j][t]=(f[j][t]*C[i-j+1])%MOD;
		}
		int nx=i+1;
		if(nx<=n){
			if(a[nx]!=-1){
				FOR(j,1,nx-1){
					if(a[nx]<=nx-j) X[j][nx]=f[j][a[nx]];
					else X[j][nx]=0;
				}
			}
			else{
				FOR(j,1,nx-1){
					int ss=0;
					FOR(t,1,nx-j) ss+=f[j][t];
					X[j][nx]=ss%MOD;
				}
			}
		}
	}
	int mt=0;
	FOR(i,1,n) mt=(mt+f[1][i])%MOD;
	if(mt>=MOD) mt-=MOD;
	FOR(i,1,n) mt=(mt*i)%MOD;
	cout << mt <<el;
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	C[1]=1;
	FOR(i,2,500) C[i]=((MOD-MOD/i) * C[MOD%i])%MOD;
	yuht hnim();
}
//100077958169269
//iloveMT
//MT^^





