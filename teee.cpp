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
int n, m;
int r[N], par[N];
vector<int> ch[N];
int dep[N], ord[N], osz;
int sz[N], hv[N];
int hd[N], pos[N], tim;

ll b1[N], b2[N];

void clr(int n){
    f1(i,n+5) { b1[i]=0; b2[i]=0; }
}

void add(ll b[], int i, ll v, int n){
    for(; i<=n; i+=i&-i) b[i]+=v;
}

ll sum(ll b[], int i){
    ll s=0;
    for(; i>0; i-=i&-i) s+=b[i];
    return s;
}

void ran(int l,int r,ll v,int n){
    if(l>r) return;
    add(b1,l,v,n);
    add(b1,r+1,-v,n);
    add(b2,l,v*(l-1),n);
    add(b2,r+1,-v*r,n);
}

ll pree(int i){
    return sum(b1,i)*i - sum(b2,i);
}

ll srx(int l,int r){
    if(l>r) return 0;
    return pree(r)-pree(l-1);
}

void tree(){
    f1(i,n) {
        ch[i].clear();
        par[i]=0;
    }
    r[n]=0;
    f1(i,n-1) {
        par[i]=r[i];
        ch[r[i]].push_back(i);
    }
    par[n]=0;
}

void orx(){
    osz=0;
    vt st;
    st.pb(n);
    dep[n]=0;
    while(!st.empty()){
        int u=st.back(); st.pop_back();
        ord[++osz]=u;
        for(int v:ch[u]){
            dep[v]=dep[u]+1;
            st.pb(v);
        }
    }
}

void xxx(){
    f1(i,osz){
        int u=ord[i];
        sz[u]=1;
        hv[u]=-1;
    }
    for(int i=osz;i>=1;i--){
        int u=ord[i], best=-1;
        for(int v:ch[u]){
            sz[u]+=sz[v];
            if(best==-1||sz[v]>sz[best]) best=v;
        }
        hv[u]=best;
    }
}

void hld(){
    tim=0;
    vt st;
    st.pb(n);
    while(!st.empty()){
        int s=st.back(); st.pop_back();
        int u=s, h=s;
        while(u!=-1){
            hd[u]=h;
            pos[u]=++tim;
            for(int v: ch[u]) if(v!=hv[u]) st.push_back(v);
            u=hv[u];
        }
    }
}

void upd(int u){
    while(u){
        int h=hd[u];
        ran(pos[h],pos[u],1,n);
        u=par[h];
    }
}

ll path(int u){
    ll res=0;
    while(u){
        int h=hd[u];
        res+=srx(pos[h],pos[u]);
        u=par[h];
    }
    return res;
}

void solve(){
    cin>>n>>m;
    f1(i,n) r[i]=i+1;
    r[n]=0;
    f0(i,m) {
        int u,v; cin>>u>>v;
        maximize(r[u],v);
    }
    tree();orx(); xxx();hld();

    int md=0;
    f1(i,n) maximize(md,dep[i]);
    vt g[md+1];
    f1(i,n) g[dep[i]].pb(i);

    clr(n);

    ll ans=0, sd=0, cnt=0;
    f0(d, md+1) {
        for(int u: g[d]){
            sd += d;
            cnt++;
            upd(u);
        }
        for(int u: g[d]){
            ll l = path(u);
            ans += sd - (l - cnt);
        }
    }
    cout<<ans<<el;
}


//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
}
//_iyf





