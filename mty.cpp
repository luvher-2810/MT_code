#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define mint __int128
#define int long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define iii pair<int, pair<int, int> >
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK "DISCHARG"
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
const int N = 1e6+10;
const ll INF = 1e18;
//--------------------------------------------------
struct L{
    int m,b,x;
};
int n;
int t[N], f[N];

int divup(int a,int b){
    if(a>=0) return (a+b-1)/b;
    return -((-a)/b);
}

int isect(L a,L b){
    return divup(b.b-a.b,a.m-b.m);
}

bool bad(L a,L b,L c){
    mint x = (mint)(b.b - a.b) * (b.m - c.m);
    mint y = (mint)(c.b - b.b) * (a.m - b.m);
    return x >= y;
}

//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin>> n;
    FOR(i,1,n) cin>>t[i];

    vector<L> h,st;
    vector<int> op;

    f[n+1]=0;

    FORD(i,n,1){
        int v=t[i], best=f[i+1];

        while(!h.empty() && h.back().m<=v){
            best=min(best,h.back().b);

            int k=op.back(); op.pop_back();
            h.pop_back();

            while((int)st.size()>k){
                h.pb(st.back());
                st.pop_back();
            }
        }

        int k=st.size();
        L nw={v,best,-INF};

        while(h.size()>=2 && bad(h[h.size()-2],h.back(),nw)){
            st.pb(h.back());
            h.pop_back();
        }

        if(!h.empty()) nw.x=isect(h.back(),nw);
        h.pb(nw);
        op.pb(k);

        int X=n-i+1;

        int l=0,r=h.size()-1;
        while(l<r){
            int m=(l+r+1)>>1;
            if(h[m].x<=X) l=m;
            else r=m-1;
        }

        f[i]=h[l].m*X + h[l].b;
    }

    cout<<f[1];	
}
//100077958169269
//iloveMT



