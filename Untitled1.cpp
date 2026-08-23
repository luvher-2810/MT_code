#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
#define MT ""
#define el "\n"
#define miti pair<ll,ll>
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
const ll INF = 1e18;
//----------------------MT---------------------------
int f[N][3];
int n;
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++){
		int x,y,z;cin >> x >> y >> z;
		f[i][0]=max(f[i-1][1]+x, f[i-1][2]+x);
		f[i][1]=max(f[i-1][0]+y, f[i-1][2]+y);
		f[i][2]=max(f[i-1][1]+z, f[i-1][0]+z);
	}
	cout << max(f[n][1],max(f[n][0], f[n][2]));
}
//100077958169269
//iloveMT


