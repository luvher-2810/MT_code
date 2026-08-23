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
const ll INF = MASK(62);
//--------------------------------------------------
int n,m,s,f,q;
vector<ii> g[N];

ll ds[N], dt[N];
int p[N], pos[N], L[N], R[N];
int u[N], v[N], w[N], ord[N];

struct IT{
    ll lz[4*N];
    void build(int id,int l,int r){
        lz[id]=INF;
        if(l==r) return;
        int m=(l+r)>>1;
        build(id<<1,l,m);
        build(id<<1|1,m+1,r);
    }
    void upd(int id,int l,int r,int u,int v,ll val){
        if(v<l||r<u) return;
        if(u<=l&&r<=v){
            lz[id]=min(lz[id],val);
            return;
        }
        int m=(l+r)>>1;
        upd(id<<1,l,m,u,v,val);
        upd(id<<1|1,m+1,r,u,v,val);
    }
    ll get(int id,int l,int r,int p,ll cur=INF){
        cur=min(cur,lz[id]);
        if(l==r) return cur;
        int m=(l+r)>>1;
        if(p<=m) return get(id<<1,l,m,p,cur);
        return get(id<<1|1,m+1,r,p,cur);
    }
} st;

void dijk(int s,ll d[]){
    FOR(i,0,n-1) d[i]=INF;
    priority_queue<ii,vector<ii>,greater<ii>> pq;
    d[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        ii it=pq.top(); pq.pop();
        int du=it.fi, x=it.se;
        if(du!=d[x]) continue;
        for(auto &e:g[x]){
            int y=e.fi, c=e.se;
            if(d[y]>du+c){
                d[y]=du+c;
                pq.push({d[y],y});
            }
        }
    }
}


//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
cin>>n>>m;
    FOR(i,0,m-1){
        cin>>u[i]>>v[i]>>w[i];
        g[u[i]].pb({v[i],w[i]});
        g[v[i]].pb({u[i],w[i]});
    }

    cin>>s>>f>>q;

    dijk(s,ds);
    dijk(f,dt);

    if(ds[f]>=INF/2){
        while(q--){
            int x,y; cin>>x>>y;
            cout<<-1<<el;
        }
        return 0;
    }

    FOR(i,0,n-1) p[i]=-1;
    priority_queue<ii,vector<ii>,greater<ii>> pq;
    pq.push({0,s});
    p[s]=-2;

    while(!pq.empty()){
        ii it =pq.top(); pq.pop();
        int du=it.fi, x=it.se;
        if(du!=ds[x]) continue;
        for(auto &e:g[x]){
            int y=e.fi, c=e.se;
            if(ds[x]+c==ds[y] && p[y]==-1){
                p[y]=x;
                pq.push({ds[y],y});
            }
        }
    }

    vector<int> path;
    for(int x=f;x!=-2;x=p[x]) path.pb(x);
    reverse(path.begin(),path.end());

    int k=path.size()-1;

    FOR(i,0,n-1) pos[i]=-1;
    FOR(i,0,(int)path.size()-1) pos[path[i]]=i;

    FOR(i,0,n-1){
        L[i]=-1;
        R[i]=k+1;
    }

    FOR(i,0,path.size()-1){
        int x=path[i];
        L[x]=R[x]=i;
    }
    FOR(i,0,n-1) ord[i]=i;

    sort(ord,ord+n,[&](int a,int b){
        if(ds[a]!=ds[b]) return ds[a]<ds[b];
        return a<b;
    });

    FOR(i,0,n-1){
        int x=ord[i];
        for(auto &e:g[x]){
            int y=e.fi, c=e.se;
            if(ds[x]+c==ds[y]) maximize(L[y],L[x]);
        }
    }

    sort(ord,ord+n,[&](int a,int b){
        if(dt[a]!=dt[b]) return dt[a]<dt[b];
        return a<b;
    });

    FOR(i,0,n-1){
        int x=ord[i];
        for(auto &e:g[x]){
            int y=e.fi, c=e.se;
            if(dt[x]+c==dt[y]) minimize(R[y],R[x]);
        }
    }

    if(k>0) st.build(1,0,k-1);

    FOR(i,0,m-1){
        int a=u[i], b=v[i], c=w[i];

        if(pos[a]!=-1 && pos[b]!=-1 && abs(pos[a]-pos[b])==1) continue;

        if(ds[a]<INF/2 && dt[b]<INF/2 && L[a]<=R[b]-1){
            int l=max(0LL,L[a]);
            int r=min((ll)k-1,R[b]-1);
            if(l<=r) st.upd(1,0,k-1,l,r,ds[a]+c+dt[b]);
        }

        if(ds[b]<INF/2 && dt[a]<INF/2 && L[b]<=R[a]-1){
            int l=max(0LL,L[b]);
            int r=min((ll)k-1,R[a]-1);
            if(l<=r) st.upd(1,0,k-1,l,r,ds[b]+c+dt[a]);
        }
    }

    ll base=ds[f];

    while(q--){
        int a,b; cin>>a>>b;
        if(pos[a]!=-1 && pos[b]!=-1 && abs(pos[a]-pos[b])==1){
            int id=min(pos[a],pos[b]);
            ll res=st.get(1,0,k-1,id);
            if(res>=INF/2) cout<<-1<<el;
            else cout<<res<<el;
        } else cout<<base<<el;
    }

}
//100077958169269
//iloveMT



