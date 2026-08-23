#include<bits/stdc++.h>
using namespace std;
#define int short
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
#define mity pair<int,int>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt")
//#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < (b) ? a = (b), 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > (b) ? a = (b), 1 : 0;
}
const int N = 1e4+1;
const int maxn =1e3+1;
const ll INF = 1e18;
int n,m;
int v[N],w[N],pos[N], dp[maxn];
inline void solve(){
	cin >> n >> m;
	for(int i=1;i<=n;i++) cin >> w[i];
	for(int i=1;i<=n;i++) cin >> v[i];
	for(int i=1;i<=n;i++) pos[i]=i;
	sort(pos+1,pos+n+1,[&](const int &i, const int &j){
		return (w[i]==w[j]) ? v[i]>v[j] : w[i]<w[j];
	});
	memset(dp,0,sizeof dp);
	vector<mity> tz[maxn];
	tz[0].pb({0,0}); dp[0]=0;
	for(int k=1;k<=n;k++){
		int i=pos[k];
		for(int j=m;j>=w[i];j--){
			if(!tz[j-w[i]].empty() && maximize(dp[j],dp[i-w[j]]+v[i])){
				tz[j].pb({i, (int)tz[j-w[i]].size()-1});
			}
		}
	}
	int bet=0, id=0;
	for(int i=0;i<=m;i++){
		if(dp[bet]<dp[i]){
			bet=i;
			id=(int)tz[bet].size()-1;
		}		
	}
	cout << dp[bet]-1<<" ";
	vector<int> ans;
	while(bet>0){
		int i, pre;
		tie(i, pre)=tz[bet][id];
		ans.pb(i);
		tie(bet,id)=make_pair(bet-w[i],pre);
	}
	cout << ans.size()<<el;
	sort(ans.begin(),ans.end());
	for(int it : ans) cout << it << " ";
}
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--){
		solve();
	} 
}
//100077958169269
//iloveMT

