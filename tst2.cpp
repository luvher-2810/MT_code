#include <bits/stdc++.h>
using namespace std;
static const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> dp(n + 1, 0);
        dp[n] = 1;

        // iterate start position
        for (int i = n - 1; i >= 0; --i) {
            int m = n - i;
            // build b = a[i..n-1]
            // compute Z for b
            vector<int> b(m);
            for (int j = 0; j < m; ++j) b[j] = a[i + j];

            vector<int> z(m, 0);
            int L = 0, R = 0;
            for (int k = 1; k < m; ++k) {
                if (k <= R) z[k] = min(R - k + 1, z[k - L]);
                while (k + z[k] < m && b[z[k]] == b[k + z[k]]) ++z[k];
                if (k + z[k] - 1 > R) {
                    L = k;
                    R = k + z[k] - 1;
                }
            }

            // mark covered prefix lengths that have a border using difference array
            // prefix lengths are 1..m
            vector<int> diff(m + 3, 0);
            for (int k = 1; k < m; ++k) {
                if (z[k] > 0) {
                    int l = k + 1;
                    int r = min(m, k + z[k]);
                    diff[l] += 1;
                    diff[r + 1] -= 1;
                }
            }
            vector<int> cover(m + 1, 0);
            int cur = 0;
            for (int len = 1; len <= m; ++len) {
                cur += diff[len];
                cover[len] = (cur > 0);
            }

            long long ways = 0;
            // for each prefix length L = j+1, if no border then add dp[i+L]
            for (int j = 0; j < m; ++j) {
                int len = j + 1;
                if (!cover[len]) {
                    ways += dp[i + len];
                    if (ways >= MOD) ways -= MOD;
                }
            }
            dp[i] = (int)(ways % MOD);
        }

        cout << dp[0] << '\n';
    }

    return 0;
}
