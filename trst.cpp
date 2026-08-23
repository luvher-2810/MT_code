#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> a(N + 1);
    int M = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
        M = max(M, a[i]);
    }

    vector<vector<int>> pos(M + 1);
    for (int i = 1; i <= N; ++i) {
        pos[a[i]].push_back(i);
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;

        vector<int> cnt(M + 1, 0);
        for (int v = 1; v <= M; ++v) {
            auto it1 = lower_bound(pos[v].begin(), pos[v].end(), L);
            auto it2 = upper_bound(pos[v].begin(), pos[v].end(), R);
            cnt[v] = int(it2 - it1);
        }

        vector<ll> prefCnt(M + 1, 0), prefSum(M + 1, 0);
        for (int v = 1; v <= M; ++v) {
            prefCnt[v] = prefCnt[v - 1] + cnt[v];
            prefSum[v] = prefSum[v - 1] + 1LL * cnt[v] * v;
        }

        ll ans = 0;

        for (int y = 1; y <= M; ++y) {
            if (cnt[y] == 0) continue;

            ll Fy = prefSum[y - 1]; // các x < y, vì x mod y = x

            for (int l = y; l <= M; l += y) {
                int r = min(M, l + y - 1);
                ll c = prefCnt[r] - prefCnt[l - 1];
                ll s = prefSum[r] - prefSum[l - 1];
                ll k = l / y; // vì l là b?i c?a y

                Fy += s - k * 1LL * y * c;
            }

            ans += 1LL * cnt[y] * Fy;
        }

        cout << ans << '\n';
    }

    return 0;
}
