#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];

        vector<int> pos(n + 1), c(n + 1), R(n + 1, 0);
        for (int i = 1; i <= n; ++i) pos[b[i]] = i;
        for (int i = 1; i <= n; ++i) c[i] = pos[a[i]];

        vector<int> mn(n + 2), mx(n + 2);
        vector<vector<pair<int,int>>> bucket(2 * n + 5);
        vector<int> ptr(2 * n + 5, 0);

        function<void(int,int)> solve = [&](int l, int r) {
            if (l >= r) return;
            int mid = (l + r) >> 1;
            solve(l, mid);
            solve(mid + 1, r);

            mn[mid] = mx[mid] = c[mid];
            for (int i = mid - 1; i >= l; --i) {
                mn[i] = min(mn[i + 1], c[i]);
                mx[i] = max(mx[i + 1], c[i]);
            }

            mn[mid + 1] = mx[mid + 1] = c[mid + 1];
            bucket[c[mid + 1] - (mid + 1) + n].push_back({c[mid + 1], mid + 1});
            for (int i = mid + 2; i <= r; ++i) {
                mn[i] = min(mn[i - 1], c[i]);
                mx[i] = max(mx[i - 1], c[i]);
                bucket[mx[i] - i + n].push_back({mn[i], i});
            }

            for (int i = mid; i >= l; --i) {
                if (mn[i] != mn[i + 1]) {
                    int j = i + mx[i] - mn[i];
                    if (j > mid && j <= r && mn[j] > mn[i] && mx[j] < mx[i]) {
                        R[i] = max(R[i], j);
                    }

                    int key = mn[i] - i + n;
                    while (ptr[key] < (int)bucket[key].size() && bucket[key][ptr[key]].first > mn[i]) {
                        ++ptr[key];
                    }
                    if (ptr[key]) {
                        int k = bucket[key][ptr[key] - 1].second;
                        if (mx[k] > mx[i]) R[i] = max(R[i], k);
                    }
                }
            }

            for (int i = mid + 1; i <= r; ++i) {
                int key = mx[i] - i + n;
                bucket[key].clear();
                ptr[key] = 0;
            }
        };

        solve(1, n);

        vector<int> st;
        int best = 0;
        for (int i = 1; i <= n; ++i) {
            while (!st.empty() && st.back() <= i) st.pop_back();
            if (R[i]) {
                st.push_back(R[i]);
                best = max(best, (int)st.size());
            }
        }

        cout << best + 1 << '\n';
    }

    return 0;
}
