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
#define f1(i,n) for(int i=1;i<=n;++i)
#define f0(i,n) for(int i=0;i<n;++i)
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
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N], b[N];
int pre[N], v[2*N];
struct BIT {
	int n, bit[N*2];
	void init(int _n){
		n=_n;
		f1(i,n) bit[i]=0;
	}
	void add(int i, int v){
		for(;i<=n;i+=i&-i) bit[i]+=v;
	}
	int sum(int i){
		int res=0;
		for(;i;i-=i&-i) res+=bit[i];
		return res;
	}
} fen;
int calc(int x){
	f1(i,n) b[i]=(a[i]>=x ? 1 : -1);
	pre[0]=0;
	f1(i,n) pre[i]=pre[i-1]+b[i];
	int m=0;
	f0(i,n+1) v[++m]=pre[i];
	sort(v+1,v+m+1);
	int sz=unique(v+1,v+m+1)-v-1;
	fen.init(sz);
	int res=0;
	f0(i,n+1) {
		int xx=lower_bound(v+1,v+sz+1,pre[i])-v;
		res+=fen.sum(xx-1);
		fen.add(xx,1);
	}
	return res;
}
int tmp[N];
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n;
	f1(i,n) cin >> a[i], tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	cout << calc(tmp[(n+1)/2])-calc(tmp[(n+1)/2]+1);
	
}






