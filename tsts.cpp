#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> f(n + 2), a(n + 2);

    for (int i = 1; i <= n; i++) cin >> f[i];

    long long s = 0, w = 0;

    for (int i = 2; i <= n - 1; i++) {
        a[i] = (f[i - 1] + f[i + 1] - 2 * f[i]) / 2;
        s += a[i];
        w += a[i] * i;
    }

    a[n] = (f[1] - w) / (n - 1);
    a[1] = f[2] - f[1] + s + a[n];

    for (int i = 1; i <= n; i++) {
        cout << a[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
