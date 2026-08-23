#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 6;      // s? d?nh
    int m = 8;      // s? c?nh
    int wmax = 10;  // tr?ng s? t?i da
    int s = 1;      // d?nh ngu?n
    cout << n << " " << m << " " << s << "\n";

    mt19937 rng(time(0));

    set<pair<int,int>> used; // tránh trùng c?nh

    for(int i = 0; i < m; i++) {
        int u, v;
        do {
            u = rng() % n + 1;
            v = rng() % n + 1;
        } while(u == v || used.count({u,v}) || used.count({v,u}));

        used.insert({u,v});

        int w = rng() % wmax + 1;
        cout << u << " " << v << " " << w << "\n";
    }
}
