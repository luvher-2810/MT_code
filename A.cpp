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
int n,k;
string s;
int ss[N];
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> k >> s;
    s = " " + s;

    deque<ii> q;
    f1(i,n) ss[i] = INF;

    for(int i = 2; i <= n-1; ++i){
        if(s[i-1] == '1' && s[i+1] == '1'){
            ss[i] = 1;
            q.pb({i, 1});
        }
    }

    while(!q.empty()){
        int t = q.front().se;
        if(t > k) break;

        vt cur;
        while(!q.empty() && q.front().se == t){
            int i = q.front().fi;
            q.pop_front();
            if(ss[i] != t) continue;
            cur.pb(i);
        }

        if(cur.empty()) continue;

        for(int it : cur){
            s[it] = (s[it] == '1' ? '0' : '1');
            ss[it] = INF;
        }

        for(int it : cur){
            for(int j = it-1; j <= it+1; ++j){
                if(j >= 2 && j <= n-1 && ss[j] == INF){
                    if(s[j-1] == '1' && s[j+1] == '1'){
                        ss[j] = t + 1;
                        q.pb({j, t+1});
                    }
                }
            }
        }
    }

    f1(i,n) cout << s[i];
}






