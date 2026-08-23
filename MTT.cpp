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
#define yuht int _=1; /*cin >> _*/; while(_--)
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
const int N = 3e5+10;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n, q;
vt adj[N];
int tin[N], revv[N], dep[N], Pos[N];
int lg2_[N << 1],st[21][N << 1], leaf[N];
int timer = 0, leafCnt=0;
vt euler;
bool active[N];
set<int> S;
struct Data{
    int u, p, idx;
};
int lca(int u, int v){
    int l = Pos[u];
    int r = Pos[v];
    if(l > r) swap(l, r);
    int k = lg2_[r - l + 1];
    int a = st[k][l];
    int b = st[k][r - MASK(k) + 1];
    return dep[a] < dep[b] ? a : b;
}

int dist(int u, int v){
    int w = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[w];
}

bool path(int a, int b, int c){
    return dist(a, b) + dist(b, c) == dist(a, c);
}

int calc(int u){
    if(!active[u]) return 0;
    if(S.size() == 1) return 1;
    auto it = S.find(tin[u]);
    auto itPrev = (it == S.begin() ? prev(S.end()) : prev(it));
    auto itNext = next(it);
    if(itNext == S.end()) itNext = S.begin();
    int p = revv[*itPrev];
    int nx = revv[*itNext];
    return !path(p, u, nx);
}

void ref(int u){
    if(!active[u]) return;
    int nw = calc(u);
    leafCnt += nw - leaf[u];
    leaf[u] = nw;
}

void apply(vt v){
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(auto x : v) ref(x);
}

void hnim(){
    cin >> n >> q;
    FOR(i,1,n-1){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<Data> stt;
    stt.pb({1,0,0});
    while(!stt.empty()){
        auto &f = stt.back();
        if(f.idx == 0){
            tin[f.u] = timer;
            revv[timer] = f.u;
            timer++;
            Pos[f.u] = euler.size();
            euler.pb(f.u);
        }
        if(f.idx == adj[f.u].size()){
            stt.pop_back();
            if(!stt.empty()) euler.pb(stt.back().u);
            continue;
        }
        int v = adj[f.u][f.idx++];
        if(v == f.p) continue;
        dep[v] = dep[f.u] + 1;
        stt.pb({v, f.u, 0});
    }
    int m = euler.size();
    FOR(i,2,m) lg2_[i] = lg2_[i/2] + 1;
    REP(i,m) st[0][i] = euler[i];
    FOR(k,1,20){
        REP(i,m){
            if(i + MASK(k) - 1 >= m) break;
            int a = st[k-1][i];
            int b = st[k-1][i + MASK(k-1)];
            st[k][i] = dep[a] < dep[b] ? a : b;
        }
    }

    while(q--){
        int x; cin >> x;
        if(!active[x]){
            if(S.empty()){
                S.insert(tin[x]);
                active[x] = 1;
                leaf[x] = 1;
                leafCnt = 1;
            }
            else{
                auto it = S.lower_bound(tin[x]);
                int p = (it == S.begin() ? revv[*prev(S.end())] : revv[*prev(it)]);
                int nx = (it == S.end() ? revv[*S.begin()] : revv[*it]);
                apply({p, nx});
                S.insert(tin[x]);
                active[x] = 1;
                leaf[x] = 0;
                apply({p, nx, x});
            }
        }
        else{
            if(S.size() == 1){
                S.clear();
                active[x] = 0;
                leaf[x] = 0;
                leafCnt = 0;
            }
            else{
                auto it = S.find(tin[x]);
                auto itPrev = (it == S.begin() ? prev(S.end()) : prev(it));
                auto itNext = next(it);
                if(itNext == S.end()) itNext = S.begin();
                int p = revv[*itPrev];
                int nx = revv[*itNext];
                apply({p, nx, x});
                S.erase(it);
                active[x] = 0;
                leaf[x] = 0;
                apply({p, nx});
            }
        }
        cout << (S.empty() ? 0 : (leafCnt + 1) / 2) << el;
    }
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




