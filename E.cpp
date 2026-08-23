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
const int N = 4e5+10;
const ll INF = 1e18;
//--------------------------------------------------
int n;
int a[N], c[N];
ii p[N];
int v[N], cc[N];
int dp[N];
int dp2[305][305];
void sub1(){
	f0(i,MASK(n)) dp[i]=INF;
	dp[0]=0;
	f0(mask,MASK(n)) {
		if(dp[mask]==INF) continue;
		int i=0;
		while(i<n && (mask & MASK(i))) i++;
		if(i==n) continue;
		for(int j=i+1;j<n;j++){
			if(mask & MASK(j) || cc[i]==cc[j]) continue;
			int xx=mask | MASK(i) | MASK(j), x1=abs(v[i]-v[j]);
			minimize(dp[xx], dp[mask]+x1);
		}
	}
	cout << dp[MASK(n)-1];
}
void sub2(){
    f1(i,n) f1(j,n) dp2[i][j]=INF;
    for(int i=1;i<n;i++){
        if(cc[i]!=cc[i+1]) dp2[i][i+1]=abs(v[i]-v[i+1]);
    }
    for(int len=4;len<=n;len+=2){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=l+1;k<=r;k++){
                if(((k-l)&1)==0) continue;
                if(cc[l]==cc[k]) continue;
                ll left = (l+1<=k-1)?dp2[l+1][k-1]:0;
                ll right = (k+1<=r)?dp2[k+1][r]:0;
                if(left==INF||right==INF) continue;
                dp2[l][r]=min(dp2[l][r],left+right+abs(v[l]-v[k]));
            }
        }
    }
    cout<<dp2[1][n-1];
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n;
	f1(i,n) cin >> a[i];
	f1(i,n/2) {
		int x,y; cin >> x >> y;
		c[x]=c[y]=i;
	}
	f1(i,n) p[i]={a[i],c[i]};
	sort(p+1,p+n+1);
	f0(i,n) {
		v[i]=p[i+1].fi;
		cc[i]=p[i+1].se;
	}
	if(n<=18) sub1();
	else sub2();
}






