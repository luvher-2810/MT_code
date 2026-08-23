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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
#define yuht int _; cin >> _; while(_--)
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
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
struct IT{
    int mn[4*N], mx[4*N];

    void build(int id, int l, int r){
        if(l==r){
            mn[id] = mx[id] = pos[l];
            return;
        }
        int mid=(l+r)/2;
        build(id*2, l, mid);
        build(id*2+1, mid+1, r);
        mn[id] = min(mn[id*2], mn[id*2+1]);
        mx[id] = max(mx[id*2], mx[id*2+1]);
    }

    void upd(int id, int l, int r, int u, int v){
        if(l==r){
            mn[id] = mx[id] = v;
            return;
        }
        int mid=(l+r)/2;
        if(u<=mid) upd(id*2,l,mid,u,v);
        else upd(id*2+1,mid+1,r,u,v);
        mn[id] = min(mn[id*2], mn[id*2+1]);
        mx[id] = max(mx[id*2], mx[id*2+1]);
    }

    int fis(int id, int l, int r, int u, int v, int xx){
        if(v<l || r<u || mn[id] >= xx) return -1;
        if(u<=l && r<=v && mx[id] < xx) return l;
        if(l==r) return l;
        int mid=(l+r)/2;
        int kk=fis(id*2,l,mid,u,v,xx);
        if(kk!=-1) return kk;
        return fis(id*2+1,mid+1,r,u,v,xx);
    }

    int las(int id, int l, int r, int u, int v, int xx){
        if(v<l || r<u || mn[id] >= xx) return -1;
        if(u<=l && r<=v && mx[id] < xx) return r;
        if(l==r) return l;
        int mid=(l+r)/2;
        int kk=las(id*2+1,mid+1,r,u,v,xx);
        if(kk!=-1) return kk;
        return las(id*2,l,mid,u,v,xx);
    }
} seg;

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	yuht hnim();
}
//100077958169269
//iloveMT




