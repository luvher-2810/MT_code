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
const int N = 2e5+10;
const ll INF = 4e18;
//--------------------------------------------------
int n,q;
ll a[N],b[N];

namespace sub1 {
    ll dfs(ll a[], int n){
        if(n == 0) return 0;
        ll res = 0;
        f1(i,n-1) {
            ll gain = llabs(a[i] - a[i+1]);
            ll tmp[10];
            int p = 0;
            f1(j,i-1)tmp[++p] = a[j];
            for(int j=i+2;j<=n;j++) tmp[++p] = a[j];
            maximize(res, gain + dfs(tmp, p));
        }
        return res;
    }
    ll solve(int m){
        return dfs(b, m);
    }
}

namespace sub2 {
    ll dp[MASK(15)];
    ll solve(int m){
        f0(i,MASK(m)) dp[i] = -INF;
        dp[0] = 0;
        f0(mask, MASK(m)){
            if(dp[mask] == -INF) continue;
            int idx[20], sz = 0;
            f1(i,m) if(!(mask & MASK(i-1))) idx[++sz] = i;
            f1(i,sz-1) {
                int u = idx[i], v = idx[i+1];
                int nmask = mask | (1 << (u-1)) | (1 << (v-1));
                dp[nmask] = max(dp[nmask], dp[mask] + llabs(b[u] - b[v]));
            }
        }
        return dp[MASK(m)-1];
    }
}

namespace sub3 {
    ll dp[2005][2005];
    ll solve(int m){
       f1(i,m) f1(j,m) dp[i][j] = -INF;

        f1(i,m-1) dp[i][i+1] = llabs(b[i] - b[i+1]);

        for(int len=4; len<=m; len+=2){
            f1(i,m-len+1){
                int j = i + len - 1;
                ll best = -INF;
                for(int k=i+1;k<=j;k+=2){
                    ll left = (k-1 >= i+1 ? dp[i+1][k-1] : 0);
                    ll right = (k+1 <= j ? dp[k+1][j] : 0);
                    maximize(best, left + right + llabs(b[i] - b[k]));
                }
                dp[i][j] = best;
            }
        }
        return dp[1][m];
    }
}
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
    cin >> n >> q;
    f1(i,n) cin >> a[i];

    while(q--){
        int l, r;
        cin >> l >> r;
        int m = 0;
        for(int i=l;i<=r;i++) b[++m] = a[i];
        if(m <= 8) cout << sub1::solve(m) << el;
        else if(m <= 15) cout << sub2::solve(m) << el;
        else cout << sub3::solve(m) << el;
    }
}






