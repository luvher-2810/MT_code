#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (LLONG_MAX / 4);

struct Edge {
    int to;
    ll w;
};

struct PairEdge {
    int u, v;
    ll d;
};

struct Query {
    int idx;
    int s;
    ll d;
};

struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        p.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
    int sizeOf(int x) {
        return sz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<vector<Edge> > g(N + 1);
        for (int i = 0; i < M; i++) {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            g[u].push_back({v, c});
            g[v].push_back({u, c});
        }

        vector<Query> queries(K);
        for (int i = 0; i < K; i++) {
            cin >> queries[i].s >> queries[i].d;
            queries[i].idx = i;
        }

        vector<PairEdge> pairs;
        pairs.reserve((ll)N * (N - 1) / 2);

        vector<ll> dist(N + 1);

        for (int src = 1; src <= N; src++) {
            for (int i = 1; i <= N; i++) dist[i] = INF;
            priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
            dist[src] = 0;
            pq.push(make_pair(0, src));

            while (!pq.empty()) {
                pair<ll, int> cur = pq.top();
                pq.pop();
                ll d = cur.first;
                int u = cur.second;
                if (d != dist[u]) continue;
                for (size_t i = 0; i < g[u].size(); i++) {
                    int v = g[u][i].to;
                    ll nd = d + g[u][i].w;
                    if (nd < dist[v]) {
                        dist[v] = nd;
                        pq.push(make_pair(nd, v));
                    }
                }
            }

            for (int v = src + 1; v <= N; v++) {
                if (dist[v] < INF) {
                    pairs.push_back({src, v, dist[v]});
                }
            }
        }

        sort(pairs.begin(), pairs.end(), [](const PairEdge &a, const PairEdge &b) {
            return a.d < b.d;
        });

        vector<Query> qsorted = queries;
        sort(qsorted.begin(), qsorted.end(), [](const Query &a, const Query &b) {
            return a.d < b.d;
        });

        DSU dsu(N);
        vector<int> ans(K);

        int ptr = 0;
        for (size_t i = 0; i < qsorted.size(); i++) {
            while (ptr < (int)pairs.size() && pairs[ptr].d <= qsorted[i].d) {
                dsu.unite(pairs[ptr].u, pairs[ptr].v);
                ptr++;
            }
            ans[qsorted[i].idx] = dsu.sizeOf(qsorted[i].s);
        }

        for (int i = 0; i < K; i++) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}

