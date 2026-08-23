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
const int N = 4e5+10;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,k;
int a[N], pre[N], dp[N];
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	cin >> n >> k;
	pre[0]=0;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		pre[i]=pre[i-1]+a[i];
	}
	deque<int> dq;
	dq.pb(-1);
	for(int i=1;i<=n;i++){
		while(!dq.empty() && dq.front()<i-k-1) dq.pop_front();
		int bet=INF;
		if(!dq.empty()){
			int x=dq.front(), prev=(x>=0?dp[x]:0), xx=prev-pre[x+1];
			bet=pre[i]+xx;
		}
		dp[i]=dp[i-1];
		if(bet!=INF) maximize(dp[i],bet);
		int nw=dp[i]-pre[i+1];
		while(!dq.empty()){
			int xx=dq.back(), vl=(xx>=0 ? dp[xx] : 0) -pre[xx+1];
			if(vl<=nw) dq.pop_back();
			else break;
		}
		dq.pb(i);
	}
	cout << dp[n];
}
//100077958169269
//iloveMT


