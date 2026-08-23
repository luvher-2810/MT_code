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
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT "POST"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
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
const int LG = 20;
const int Nx = 3e5+10;
const ll INF = 1e18;
//----------------------MT---------------------------
struct BIT{
    int n;
    ll bit[Nx*2];
    void init(int n_) {
        n = n_;
        for(int i=1;i<=n;i++) bit[i]=0;
    }
    void add(int i, ll v) {
        for(; i<=n; i+=i&-i) bit[i]+=v;
    }
    ll sum(int i) {
        ll s=0;
        for(; i>0; i-=i&-i) s+=bit[i];
        return s;
    }
};
struct Ran{
    int n;
    BIT B1, B2;
    void init(int n_) {
        n = n_;
        B1.init(n);
        B2.init(n);
    }
    void add(int l, int r, ll v) {
        if(l>r) return;
        B1.add(l, v);
        B1.add(r+1, -v);
        B2.add(l, v*(l-1));
        B2.add(r+1, -v*r);
    }
    ll pfx(int x) {
        if(x<=0) return 0;
        return B1.sum(x)*x - B2.sum(x);
    }
    ll ssum(int l, int r) {
        if(l>r) return 0;
        return pfx(r) - pfx(l-1);
    }
};
int A[Nx];
int fis[Nx],ls[Nx];
int fps[Nx], lpos[Nx];
int stMin[LG][Nx], stMax[LG][Nx], rgt[Nx];
int stt[Nx], ep[Nx];
int nxt[Nx], indeg[Nx];
int visited[Nx];
int flat[Nx],base[Nx],px[Nx];
int ans[Nx];
int rmx(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
    return max(stMax[k][l], stMax[k][r-(1<<k)+1]);
}
int rmn(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
    return min(stMin[k][l], stMin[k][r-(1<<k)+1]);
}
struct Node {
    int r, flat, base;
};

struct Query {
    int u, v, id;
};
int N,Q;
Query qs[Nx + 5];
Node nd[Nx + 5];
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> A[i];

    vector<int> cmp(A + 1, A + N + 1);
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());

    for(int i = 1; i <= N; i++){
        A[i] = lower_bound(cmp.begin(), cmp.end(), A[i]) - cmp.begin() + 1;
    }

    int M = cmp.size();

    for(int i = 1; i <= M; i++){
        fis[i] = 1e9;
        ls[i] = 0;
    }

    for(int i = 1; i <= N; i++){
        fis[A[i]] = min(fis[A[i]], i);
        ls[A[i]] = max(ls[A[i]], i);
    }

    for(int i = 1; i <= N; i++){
        fps[i] = fis[A[i]];
        lpos[i] = ls[A[i]];
    }

    for(int i = 1; i <= N; i++){
        stMin[0][i] = fps[i];
        stMax[0][i] = lpos[i];
    }

    for(int k = 1; k < LG; k++){
        for(int i = 1; i + (1 << k) - 1 <= N; i++){
            stMin[k][i] = min(stMin[k - 1][i], stMin[k - 1][i + (1 << (k - 1))]);
            stMax[k][i] = max(stMax[k - 1][i], stMax[k - 1][i + (1 << (k - 1))]);
        }
    }

    for(int i = 1; i <= N; i++) rgt[i] = -1;

    for(int v = 1; v <= M; v++){
        int L = fis[v];
        int R = ls[v];
        bool ok = true;
        while(true){
            int nR = rmx(L, R);
            int mF = rmn(L, R);
            if(mF < L){
                ok = false;
                break;
            }
            if(nR == R) break;
            R = nR;
        }
        if(ok) rgt[L] = R;
    }

    int S = 0;
    for(int i = 1; i <= N; i++){
        if(fis[A[i]] == i && rgt[i] != -1){
            stt[++S] = i;
            ep[S] = rgt[i];
        }
    }

    unordered_map<int,int> id;
    id.reserve(S * 2);

    for(int i = 1; i <= S; i++) id[stt[i]] = i;

    for(int i = 1; i <= S; i++){
        nxt[i] = -1;
        indeg[i] = 0;
    }

    for(int i = 1; i <= S; i++){
        int x = ep[i] + 1;
        if(id.count(x)){
            nxt[i] = id[x];
            indeg[nxt[i]]++;
        }
    }

    int cur = 0;
    for(int i = 1; i <= S; i++){
        if(indeg[i] == 0){
            int u = i;
            int b = cur + 1;
            while(u != -1 && !visited[u]){
                visited[u] = 1;
                flat[u] = ++cur;
                base[u] = b;
                px[u] = flat[u] - b;
                u = nxt[u];
            }
        }
    }

    for(int i = 1; i <= S; i++){
        if(!visited[i]){
            int u = i;
            int b = cur + 1;
            while(u != -1 && !visited[u]){
                visited[u] = 1;
                flat[u] = ++cur;
                base[u] = b;
                px[u] = flat[u] - b;
                u = nxt[u];
            }
        }
    }

    for(int i = 1; i <= S; i++){
        nd[i] = {ep[i], flat[i], base[i]};
    }

    sort(nd + 1, nd + S + 1, [](const Node &a, const Node &b){
        return a.r < b.r;
    });

    for(int i = 1; i <= Q; i++){
        cin >> qs[i].u >> qs[i].v;
        qs[i].id = i;
    }

    sort(qs + 1, qs + Q + 1, [](const Query &a, const Query &b){
        return a.v < b.v;
    });

    Ran bit;
    bit.init(cur);

    int p = 1;
    for(int i = 1; i <= Q; i++){
        while(p <= S && nd[p].r <= qs[i].v){
            bit.add(nd[p].base, nd[p].flat, 1);
            p++;
        }
        ll res = 0;
        for(int j = 1; j <= S; j++){
            if(stt[j] >= qs[i].u && stt[j] <= qs[i].v){
                res += bit.ssum(flat[j], flat[j]);
            }
        }
        ans[qs[i].id] = res;
    }

    for(int i = 1; i <= Q; i++){
        cout << ans[i] << el;
    }
}
//100077958169269
//I love mthuyyyyyy



