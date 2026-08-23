#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define All(X) X.begin(),X.end()
#define task ""
const int MOD = 1e9+7;
const int maxn = 2e5+10;
const int INF = 1e18;
int n, a[maxn];
int f[1<<20], dp[1<<20], ndp[1<<20], C[1<<20];
int xx[25], g[25][25], len[25];
int solve(int x){
	int _i=0;
	for(int i=x;i<=n;i*=3){
		int _j=0;
		for(int j=i;j<=n;j*=2) g[_i][_j++]=a[j];
		len[_i++]=_j;
		if(i>n/3) break;
	}
	int sz=1, pre=2;
	f[0]=0;
	for(int i=0;i<_i;i++){
		int l=len[i], k=max(0ll, pre-2);
		for(int mask=0; mask<(1<<k);mask++){
			if(mask<sz) dp[mask]=f[mask];
			else dp[mask]=INF;
		}
		for(int bit=0;bit<k;bit++){
			for(int mask=0;mask<(1<<k);mask++){
				if(mask & (1<<bit) && dp[mask ^ (1<<bit)]<dp[mask]) dp[mask]=dp[mask ^ (1<<bit)];
			}
		}
		for(int mask=0;mask<(1<<(max(0ll,l-2)));mask++) ndp[mask]=INF;
		C[0]=xx[0]=0;
		for(int mask=1;mask<(1<<l);mask++){
			int t=__builtin_ctz(mask);
			C[mask]=C[mask ^ (1<<t)] +g[i][t];
		}
		if(l>=3){
			for(int mask=0;mask<(1<<l);mask++){
				int bit=0;
				for(int j=0;j<=l-3;j++) if((mask & (7<<j))==0) bit |= (1<<j);
				xx[mask]=bit;
			}
		}
		else for(int mask=0;mask<(1<<l);mask++) xx[mask]=0;
		for(int mask=0;mask<(1<<l);mask++){
			int bit=mask & ((1<<k)-1);
			if(dp[bit]==INF) continue;
			if(dp[bit]+C[mask]<ndp[xx[mask]]) ndp[xx[mask]]=dp[bit]+C[mask];
		}
		sz=(1<<(max(0ll,l-2)));
		for(int mask=0;mask<(1<<(max(0ll,l-2)));mask++) f[mask]=ndp[mask];
		pre=l;
	}
	int res=INF;
	for(int mask=0;mask<sz;mask++) res=min(res,f[mask]);
	return res;
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	int ans=0;
	for(int i=1;i<=n;i++) if(i&1 && i%3!=0) ans+=solve(i);
	cout << ans;
	return 0;
}
//luv


