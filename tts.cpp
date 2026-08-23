#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define iii pair<int, pair<int, int> >
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int N = 2e5 + 10;
const int LOG = 20;

int n, m, q;
int head[N], to[N * 2], nx[N * 2], ec;
int dep[N], up[LOG][N], add[N];
int bit[N];
int lft[N], rgt[N], room[N], tagv[N], tail;

void ae(int u, int v){
    to[++ec] = v;
    nx[ec] = head[u];
    head[u] = ec;
}

void addbit(int x, int v){
    for(; x <= m; x += x & -x) bit[x] += v;
}

int sumbit(int x){
    int s = 0;
    for(; x > 0; x -= x & -x) s += bit[x];
    return s;
}

int kth(int k){
    int pos = 0;
    for(int p = 1 << 18; p; p >>= 1){
        int np = pos + p;
        if(np <= m && bit[np] < k){
            pos = np;
            k -= bit[np];
        }
    }
    return pos + 1;
}

int getseg(int x){
    return kth(sumbit(x));
}

void bfs(){
    queue<int> qu;
    qu.push(1);
    up[0][1] = 0;
    dep[1] = 0;
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        for(int e = head[u]; e; e = nx[e]){
            int v = to[e];
            if(v == up[0][u]) continue;
            up[0][v] = u;
            dep[v] = dep[u] + 1;
            qu.push(v);
        }
    }
}

int lca(int a, int b){
    if(dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    FOR(i, 0, LOG - 1) if((d >> i) & 1) a = up[i][a];
    if(a == b) return a;
    FORD(i, LOG - 1, 0) if(up[i][a] != up[i][b]){
        a = up[i][a];
        b = up[i][b];
    }
    return up[0][a];
}

int dist(int a, int b){
    int c = lca(a, b);
    return dep[a] + dep[b] - 2 * dep[c];
}

int split(int pos){
    if(pos > m) return 0;
    int s = getseg(pos);
    if(s == pos) return s;

    int t = pos;
    room[t] = room[s];
    tagv[t] = tagv[s];
    rgt[t] = rgt[s];
    lft[t] = s;
    nx[t] = nx[s];

    if(nx[t]) lft[nx[t]] = t;
    else tail = t;

    rgt[s] = pos - 1;
    nx[s] = t;
    addbit(t, 1);
    return t;
}

bool same(int a, int b){
    return room[a] == room[b] && tagv[a] == tagv[b];
}

void merge_seg(int a, int b){
    rgt[a] = rgt[b];
    nx[a] = nx[b];
    if(nx[b]) lft[nx[b]] = a;
    else tail = a;
    addbit(b, -1);
    lft[b] = nx[b] = 0;
}

int32_t main(){
    faster;

    cin >> n >> m >> q;

    vector<int> a(m + 1);
    FOR(i, 1, m) cin >> a[i];

    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        ae(u, v);
        ae(v, u);
    }

    bfs();

    FOR(k, 1, LOG - 1) FOR(i, 1, n) up[k][i] = up[k - 1][up[k - 1][i]];

    int last = 0;
    FOR(i, 1, m){
        if(i == 1 || a[i] != a[i - 1]){
            room[i] = a[i];
            tagv[i] = 0;
            rgt[i] = i;
            if(last){
                nx[last] = i;
                lft[i] = last;
                rgt[last] = i - 1;
            }
            addbit(i, 1);
            last = i;
        }else{
            rgt[last] = i;
        }
    }
    tail = last;

    while(q--){
        char t;
        cin >> t;

        if(t == 'e'){
            int x, v;
            cin >> x >> v;
            add[x] += v;
        }else if(t == 'q'){
            int k;
            cin >> k;
            int s = getseg(k);
            cout << tagv[s] + add[room[s]] << "\n";
        }else{
            int l, r, z;
            cin >> l >> r >> z;

            int itr = split(r + 1);
            int itl = split(l);

            for(int s = itl; s != itr; s = nx[s]){
                int old = room[s];
                tagv[s] += add[old] - add[z] - dist(old, z);
                room[s] = z;
            }

            int s = itl;
            while(lft[s] && same(lft[s], s)){
                int p = lft[s];
                merge_seg(p, s);
                s = p;
            }

            int cur = s;
            while(cur != itr){
                int ns = nx[cur];
                if(ns && ns != itr && same(cur, ns)){
                    merge_seg(cur, ns);
                }else{
                    cur = ns;
                }
            }

            while(itr && lft[itr] && same(lft[itr], itr)){
                int p = lft[itr];
                merge_seg(p, itr);
                itr = p;
            }
        }
    }

    return 0;
}
