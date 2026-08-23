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
const int MOD = 998244353;
const int mod = 998244353;
const int N = 2e5+10;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
ll pw(ll x, ll y){
    ll ans = 1;
    ll mul = x;
    while(y > 0){
        if(y & 1) {
            ans = 1ll * ans * mul % MOD;
        }
        mul = 1ll * mul * mul % MOD;
        y >>= 1;
    }
    return ans;
} 
int INV(int x) {return pw(x, MOD-2);}
struct NTT{
	void ntt(vt &a, bool inv){
		int n=a.size();
		for(int i=1,j=0;i<n;i++){
			int b=(n>>1);
			for(;j&b;b>>=1) j^=b;
			j^=b;
			if(i<j) swap(a[i], a[j]);
		}
		for(int x=2;x<=n;x<<=1){
			int w=pw(3, (MOD-1)/x);
			if(inv) w=INV(w);
			for(int i=0;i<n;i+=x){
				int cur=1;
				for(int j=0;j<x/2;j++){
					int u=a[i+j];
					int v=a[i+j+x/2]*cur%MOD;
					a[i+j]=(u+v)%MOD;
					a[i+j+x/2]=(u-v+MOD)%MOD;
					cur=cur*w%MOD;
				}
			}
		}
		if(inv){
			int in=INV(n);
			for(int &x : a) x=x*in%MOD;	
		}
	}
} fft;
struct Matrix{
	int a,b,c,d;
	Matrix operator * (const Matrix &x) const{
		return {(a*x.a+b*x.c)%MOD,(a*x.b+b*x.d)%MOD,(c*x.a+d*x.c)%MOD,(c*x.b+d*x.d)%MOD};
	}
};
Matrix MulMt(Matrix x, ll y){
	Matrix res={1,0,0,1};
	while(y>0){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
int calc(int a, int b, int x){
	if(x==0) return 1;
	Matrix M={a,b,1,0};
	Matrix P=MulMt(M,x);
	return P.a;
}
int n,m;

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> n >> m;
	int X=1;
	while(X<=4*(n-1)) X*=2;
	int w=pw(3,(MOD-1)/X);
	int inv=INV(w), f=pw(w,(2*(n-1))%X);
	vt mt(X);
	int z=1, fac=1, iv=1;
	FOR(i,0,X-1){
		int A=(z*z+iv*iv)%MOD, B=(z+iv)%MOD;
		int k=calc(A,B,n-1);
		mt[i]=fac*k%MOD;
		z=z*w%MOD;
		iv=iv*inv%MOD;
		fac=fac*f%MOD;
	}
	fft.ntt(mt, 1);
	FOR(i,1,m){
		int pos=2*(n-1)+i-1;
		if(pos>=X) cout << 0 <<el;
		else cout << mt[pos]%MOD<<el;
	}
}
//100077958169269
//iloveMT

