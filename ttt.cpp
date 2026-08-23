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
//--------------------------------------------------

struct NODE{
    int mx[3], ms;
    int mn[2], ns;
    NODE(){ 
		ms = ns = 0; 
	}
};

int n,q,a[N];
NODE st[4*N];

NODE merge(const NODE &l, const NODE &r){
    NODE t;
    int tmp[6];
    int cnt = 0;
    REP(i,l.ms) tmp[cnt++]=l.mx[i];
    REP(i,r.ms) tmp[cnt++]=r.mx[i];
    if(cnt>0){
        sort(tmp, tmp+cnt, greater<int>());
        t.ms = min(3ll, cnt);
        REP(i,t.ms) t.mx[i]=tmp[i];
    }else t.ms=0;

    int tmp2[4];
    int cnt2=0;
    REP(i,l.ms) tmp2[cnt2++]=l.mn[i];
    REP(i,r.ms) tmp2[cnt2++]=r.mn[i];
    if(cnt2>0){
        sort(tmp2, tmp2+cnt2); 
        t.ns = min(2ll, cnt2);
        REP(i,t.ms) t.mn[i]=tmp2[i];
    }else t.ns=0;

    return t;
}
void build(int id,int l,int r){
    if(l==r){
        st[id]=NODE();
        st[id].mx[0]=a[l];
        st[id].mn[0]=a[l];
        st[id].ms=st[id].ns=1;
        return;
    }
    int m=(l+r)>>1;
    build(id<<1,l,m);
    build(id<<1|1,m+1,r);
    st[id]=merge(st[id<<1],st[id<<1|1]);
}

NODE qr(int id,int l,int r,int u,int v){
    if(u<=l && r<=v) return st[id];
    int m=(l+r)>>1;
    if(v<=m) return qr(id<<1,l,m,u,v);
    if(u>m) return qr(id<<1|1,m+1,r,u,v);
    return merge(qr(id<<1,l,m,u,v), qr(id<<1|1,m+1,r,u,v));
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    build(1,1,n);
    while(q--){
        int l,r; cin >> l >> r;
        NODE t=qr(1,1,n,l,r);
        int ans=-INF;
        if(t.ms>=3) maximize(ans,t.mx[0]*t.mx[1]*t.mx[2]);
        if(t.ms>=1 && t.ns>=2) maximize(ans,t.mx[0]*t.mn[0]*t.mn[1]);
        cout << ans << el;
    }
}
//100077958169269
//iloveMT



