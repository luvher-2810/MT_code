#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<ll> bit;

    Fenwick() {}

    Fenwick(int n) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int i, ll v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }

    ll sum(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }

    ll range_sum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }

    int kth(int k) const {
        int idx = 0;
        int pw = 1;

        while ((pw << 1) <= n) pw <<= 1;

        for (int step = pw; step; step >>= 1) {
            int nxt = idx + step;
            if (nxt <= n && bit[nxt] < k) {
                idx = nxt;
                k -= (int)bit[nxt];
            }
        }

        return idx + 1;
    }
};

struct SegTree {
    int n;
    vector<int> mn;

    SegTree() {}

    SegTree(int n) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        mn.assign(4 * n + 4, INT_MAX);
    }

    void build(int id, int l, int r, const vector<int> &pos) {
        if (l == r) {
            mn[id] = pos[l];
            return;
        }

        int mid = (l + r) >> 1;

        build(id << 1, l, mid, pos);
        build(id << 1 | 1, mid + 1, r, pos);

        mn[id] = min(mn[id << 1], mn[id << 1 | 1]);
    }

    void update(int id, int l, int r, int idx, int val) {
        if (l == r) {
            mn[id] = val;
            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid)
            update(id << 1, l, mid, idx, val);
        else
            update(id << 1 | 1, mid + 1, r, idx, val);

        mn[id] = min(mn[id << 1], mn[id << 1 | 1]);
    }

    int findFirst(int id, int l, int r, int ql, int qr, int lim) const {
        if (qr < l || r < ql || mn[id] >= lim) return -1;

        if (l == r) return l;

        int mid = (l + r) >> 1;

        int res = findFirst(id << 1, l, mid, ql, qr, lim);

        if (res != -1) return res;

        return findFirst(id << 1 | 1, mid + 1, r, ql, qr, lim);
    }

    int findLast(int id, int l, int r, int ql, int qr, int lim) const {
        if (qr < l || r < ql || mn[id] >= lim) return -1;

        if (l == r) return l;

        int mid = (l + r) >> 1;

        int res = findLast(id << 1 | 1, mid + 1, r, ql, qr, lim);

        if (res != -1) return res;

        return findLast(id << 1, l, mid, ql, qr, lim);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> f(n + 1);

    for (int i = 1; i <= n; i++) cin >> f[i];

    Fenwick fwCnt(n);

    for (int i = 1; i <= n; i++) fwCnt.add(i, 1);

    vector<int> p(n + 1), pos(n + 1);

    for (int i = n; i >= 1; i--) {
        int val = fwCnt.kth(f[i] + 1);

        p[i] = val;
        pos[val] = i;

        fwCnt.add(val, -1);
    }

    Fenwick fwSum(n);

    for (int i = 1; i <= n; i++) fwSum.add(i, p[i]);

    SegTree st(n);

    st.build(1, 1, n, pos);

    auto swapValues = [&](int a, int b) {
        if (a == b) return;

        int pa = pos[a];
        int pb = pos[b];

        fwSum.add(pa, (ll)b - a);
        fwSum.add(pb, (ll)a - b);

        p[pa] = b;
        p[pb] = a;

        pos[a] = pb;
        pos[b] = pa;

        st.update(1, 1, n, a, pb);
        st.update(1, 1, n, b, pa);
    };

    while (q--) {
        char type;
        cin >> type;

        if (type == '?') {
            int l, r;
            cin >> l >> r;

            cout << fwSum.range_sum(l, r) << '\n';
        }
        else if (type == '+') {
            int i;
            cin >> i;

            int x = p[i];

            int y = st.findFirst(1, 1, n, x + 1, n, i);

            swapValues(x, y);
        }
        else {
            int i;
            cin >> i;

            int x = p[i];

            int y = st.findLast(1, 1, n, 1, x - 1, i);

            swapValues(x, y);
        }
    }

    return 0;
}
