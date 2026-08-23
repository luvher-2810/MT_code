#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

pair<vector<int>, vector<long long>> find_rebalancing_strategy(
    int N,
    vector<int> A,
    vector<int> B,
    vector<int> U,
    vector<int> V
) {
    int M = 2 * (N - 1);

    vector<int> head(N, -1), to(M), nxt(M);
    int ec = 0;

    for (int i = 0; i < N - 1; i++) {
        to[ec] = V[i];
        nxt[ec] = head[U[i]];
        head[U[i]] = ec++;

        to[ec] = U[i];
        nxt[ec] = head[V[i]];
        head[V[i]] = ec++;
    }

    vector<ll> d(N);
    int K = 0;

    for (int i = 0; i < N; i++) {
        d[i] = (ll)A[i] - B[i];
        if (d[i] != 0) K++;
    }

    vector<int> par(N, -2), ord;
    ord.reserve(N);

    par[0] = -1;
    ord.push_back(0);

    for (int it = 0; it < N; it++) {
        int u = ord[it];

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];

            if (v == par[u]) continue;

            par[v] = u;
            ord.push_back(v);
        }
    }

    vector<int> cnt(N, 0);
    vector<ll> sub(N, 0);

    for (int i = 0; i < N; i++) {
        cnt[i] = (d[i] != 0);
        sub[i] = d[i];
    }

    for (int it = N - 1; it > 0; it--) {
        int u = ord[it];

        cnt[par[u]] += cnt[u];
        sub[par[u]] += sub[u];
    }

    auto isH = [&](int u, int v) -> bool {
        if (par[v] == u)
            return 0 < cnt[v] && cnt[v] < K;

        if (par[u] == v)
            return 0 < cnt[u] && cnt[u] < K;

        return false;
    };

    auto compSum = [&](int u, int v) -> ll {
        if (par[v] == u)
            return sub[v];

        return -sub[u];
    };

    vector<int> upLen(N, 0), downLen(N, 0);
    vector<int> upEnd(N), downEnd(N);

    for (int i = 0; i < N; i++) {
        upEnd[i] = downEnd[i] = i;
    }

    struct Cand {
        int len;
        int child;
        int en;
    };

    auto updTop = [&](Cand &a, Cand &b, const Cand &x) {
        if (x.len > a.len) {
            b = a;
            a = x;
        } else if (x.len > b.len) {
            b = x;
        }
    };

    int bestLen = 0;
    int bestS = 0;
    int bestT = 0;
    int bestMid = 0;

    auto updBest = [&](int len, int s, int t, int mid) {
        if (len > bestLen) {
            bestLen = len;
            bestS = s;
            bestT = t;
            bestMid = mid;
        }
    };

    for (int it = N - 1; it >= 0; it--) {
        int u = ord[it];

        Cand in1{0, -1, u};
        Cand in2{0, -1, u};

        Cand out1{0, -1, u};
        Cand out2{0, -1, u};

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];

            if (par[v] != u) continue;
            if (!isH(u, v)) continue;

            if (sub[v] >= 0) {
                Cand c;
                c.len = upLen[v] + 1;
                c.child = v;
                c.en = upEnd[v];

                updTop(in1, in2, c);
            }

            if (sub[v] <= 0) {
                Cand c;
                c.len = downLen[v] + 1;
                c.child = v;
                c.en = downEnd[v];

                updTop(out1, out2, c);
            }
        }

        upLen[u] = in1.len;
        upEnd[u] = in1.en;

        downLen[u] = out1.len;
        downEnd[u] = out1.en;

        if (in1.child != -1)
            updBest(in1.len, in1.en, u, u);

        if (out1.child != -1)
            updBest(out1.len, u, out1.en, u);

        Cand ins[2] = {in1, in2};
        Cand outs[2] = {out1, out2};

        for (int a = 0; a < 2; a++) {
            if (ins[a].child == -1) continue;

            for (int b = 0; b < 2; b++) {
                if (outs[b].child == -1) continue;
                if (ins[a].child == outs[b].child) continue;

                updBest(
                    ins[a].len + outs[b].len,
                    ins[a].en,
                    outs[b].en,
                    u
                );
            }
        }
    }

    vector<int> path, tmp;

    int x = bestS;

    while (x != bestMid) {
        path.push_back(x);
        x = par[x];
    }

    path.push_back(bestMid);

    x = bestT;

    while (x != bestMid) {
        tmp.push_back(x);
        x = par[x];
    }

    reverse(tmp.begin(), tmp.end());

    for (int v : tmp)
        path.push_back(v);

    vector<char> onPath(N, 0);

    for (int v : path)
        onPath[v] = 1;

    vector<int> X;
    vector<ll> Y;

    X.reserve(2 * N);
    Y.reserve(2 * N);

    ll truck = 0;

    auto addCurrent = [&](ll y) {
        Y.back() += y;

        if (y < 0)
            truck += -y;
        else
            truck -= y;
    };

    struct Frame {
        int u;
        int p;
        int e;
        int phase;
    };

    vector<Frame> st;
    st.reserve(N);

    auto excursion = [&](int root, int p) {
        X.push_back(root);
        Y.push_back(0);

        if (d[root] > 0)
            addCurrent(-d[root]);

        st.clear();
        st.push_back({root, p, head[root], 0});

        while (!st.empty()) {
            Frame &f = st.back();

            if (f.phase < 2) {
                int chosen = -1;

                while (f.e != -1) {
                    int e = f.e;
                    f.e = nxt[e];

                    int v = to[e];

                    if (v == f.p)
                        continue;

                    if (!isH(f.u, v))
                        continue;

                    ll s = compSum(f.u, v);

                    if ((f.phase == 0 && s > 0) ||
                        (f.phase == 1 && s <= 0)) {
                        chosen = v;
                        break;
                    }
                }

                if (chosen != -1) {
                    X.push_back(chosen);
                    Y.push_back(0);

                    if (d[chosen] > 0)
                        addCurrent(-d[chosen]);

                    st.push_back({
                        chosen,
                        f.u,
                        head[chosen],
                        0
                    });

                    continue;
                }

                f.phase++;
                f.e = head[f.u];
                continue;
            }

            if (d[f.u] < 0)
                addCurrent(-d[f.u]);

            int p2 = f.p;

            st.pop_back();

            X.push_back(p2);
            Y.push_back(0);
        }
    };

    X.push_back(path[0]);
    Y.push_back(0);

    for (int i = 0; i < (int)path.size(); i++) {
        int u = path[i];

        if (i > 0) {
            X.push_back(u);
            Y.push_back(0);
        }

        if (d[u] > 0)
            addCurrent(-d[u]);

        for (int phase = 0; phase < 2; phase++) {
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];

                if (onPath[v])
                    continue;

                if (!isH(u, v))
                    continue;

                ll s = compSum(u, v);

                if ((phase == 0 && s > 0) ||
                    (phase == 1 && s <= 0)) {
                    excursion(v, u);
                }
            }
        }

        if (d[u] < 0)
            addCurrent(-d[u]);
    }

    return make_pair(X, Y);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> A(N), B(N), U(N-1), V(N-1);

    for(int &x : A) cin >> x;
    for(int &x : B) cin >> x;

    for(int i=0;i<N-1;i++)
        cin >> U[i] >> V[i];

    pair<vector<int>, vector<ll> > ans =
        find_rebalancing_strategy(N,A,B,U,V);

    int k = (int)ans.first.size() - 1;

    cout << k << '\n';

    for(int i=0;i<=k;i++){
        cout << ans.first[i] << (i==k ? '\n' : ' ');
    }

    for(int i=0;i<=k;i++){
        cout << ans.second[i] << (i==k ? '\n' : ' ');
    }

    return 0;
}
