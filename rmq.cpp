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
#define sum(a) accumulate(a+1,a+n+1,0ll)
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
const int N = 1e5+10;
const int LG = 20;
const ll INF = 1e18;
//--------------------------------------------------
int n,q;
int a[N], mn[N][LG], mx[N][LG], lg2[N];

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n;
	f1(i,n) cin >> a[i];
	lg2[1]=0;
	for(int i=2;i<=n;i++) lg2[i]=lg2[i/2]+1;
	f1(i,n) mx[i][0]=mn[i][0]=a[i];
	f1(k,LG-1) f1(i,n-MASK(k)+1) {
		mn[i][k]=min(mn[i][k-1], mn[i+MASK(k-1)][k-1]);
		mx[i][k]=max(mx[i][k-1], mx[i+MASK(k-1)][k-1]);
	}
	cin >> q;
	while(q--){
		int l,r; cin >> l >> r;
		int k=lg2[r-l+1];
		cout << max(mx[l][k], mx[r-MASK(k)+1][k])<< " "<<min(mn[l][k],mn[r-MASK(k)+1][k]) << el;
	}
}






