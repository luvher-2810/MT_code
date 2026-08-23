#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define mint __int128
#define int long long
#define mp make_pair
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
#define vt vector
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
const int N = 5e5+10;
const ll INF = 4e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n,q;
int p[N],len[N];
vt<int> child[N];
int deg[N], sub[N], hev[N], pos[N];
int ID[N], off[N], xd[N];
int start[N], ln[N], pref[N], cn, fz, sz;
ii pre[N*2];
mint GCD(mint a, mint b, mint& x, mint& y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	mint x1,y1;
	mint g=GCD(b,a%b, x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return g;
}
mint INV(mint a, mint b){
	if(b==1) return 0;
	mint x,y; 
	GCD(a,b,x,y);
	x%=b;
	if(x<0) x+=b;
	return x;
}
bool ok(ii c, ll x){
    if(c.fi==0) return false;
    if(c.fi==INF) return x==c.se;
    return x%c.fi == c.se;
}

ii calc(ii A, ii B){
    if(A.fi==0 || B.fi==0) return mp(0,0);
    if(A.fi==INF && B.fi==INF) return (A.se==B.se ? A : mp(0ll,0ll));
    if(A.fi==INF) return ok(B,A.se) ? A : mp(0ll,0ll);
    if(B.fi==INF) return ok(A,B.se) ? B : mp(0ll,0ll);

    ll x1=A.fi,y1=B.fi;
    ll g=__gcd(x1,y1);

    mint kk=(mint)B.se-(mint)A.se;
    if(kk%g!=0) return mp(0,0);

    mint x2=x1/g, y2=y1/g;
    kk/=g;
    kk%=y2;
    if(kk<0) kk+=y2;

    mint inv=INV(x2%y2, y2), t=(kk*inv)%y2;
    mint xx=(mint)A.se + (mint)x1*t;
    mint yy=(mint)x1*y2;

    xx%=yy;
    if(xx<0) xx+=yy;

    if(yy<=INF) return mp((ll)yy,(ll)xx);
    if(xx<=INF) return mp(INF,(ll)xx);
    return mp(0,0);
}

ll solve(ll s){
    int u=1;
    while(1){
        int id=ID[u], st=pref[id], L=ln[id];

        int l=0,r=L;
        while(l<r){
            int mid=(l+r+1)/2;
            if(ok(pre[st+mid],s)) l=mid;
            else r=mid-1;
        }

        if(l==L) return xd[start[id]+L-1];

        int node=xd[start[id]+l];
        int i=(int)((s+off[node])%deg[node]);

        s+=off[node]+len[child[node][i]];
        u=child[node][i];
    }
}
void hnim(){
	cin >> n >> q;
	FOR(i,1,n) child[i].clear();
	FOR(i,2,n) {
		cin >> p[i];
		child[p[i]].pb(i);
	}
	FOR(i,2,n) cin >> len[i];
	FOR(i,1,n) deg[i]=child[i].size();
	FORD(u, n, 1) {
        sub[u] = 1;
        int res = 0, best = -1;
        REP(i, deg[u]) {
            int v = child[u][i];
            sub[u] += sub[v];
            if (sub[v] > best) {
                best = sub[v];
                res = v;
                pos[u] = i;
            }
        }
        hev[u] = res;
    }
	cn=fz=sz=0;
	FOR(u, 1, n) {
        if (u == 1 || hev[p[u]] != u) {
            int id = cn++;
            start[id] = sz + 1;
            pref[id] = fz + 1;

            int x = u, of = 0;
            while (1) {
                ID[x] = id;
                off[x] = of;
                xd[++sz] = x;
                if (!hev[x]) break;
                of += len[hev[x]];
                x = hev[x];
            }

            int tmp = sz - start[id] + 1;
            ln[id] = tmp;

            ii cur = {1, 0};
            pre[++fz] = cur;

            REP(i, tmp) {
                int node = xd[start[id] + i];
                ii ctt;
                if (deg[node] == 0) ctt = {1, 0};
                else {
                    int r = pos[node] - (off[node] % deg[node]);
                    r %= deg[node];
                    if (r < 0) r += deg[node];
                    ctt = {(ll)deg[node], r};
                }
                cur = calc(cur, ctt);
                pre[++fz] = cur;
            }
        }
    }

	while(q--){
		ll x; cin >> x;
		cout << solve(x)<<" ";
	}
	cout << el;
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	yuht hnim();
}
//100077958169269
//iloveMT




