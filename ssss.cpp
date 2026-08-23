#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll mod = 1e9+7;
const ll base = 311;

string s;
ll h[1000005], p[1000005];

// l?y hash do?n [l, r]
ll getHash(int l, int r){
    return (h[r] - h[l-1]*p[r-l+1] % mod + mod) % mod;
}

int main(){
    cin >> s;
    int n = s.size();

    s = " " + s; // index t? 1

    // tính p[i] = base^i
    p[0] = 1;
    for(int i = 1; i <= n; i++){
        p[i] = (p[i-1] * base) % mod;
    }

    // tính hash prefix
    for(int i = 1; i <= n; i++){
        h[i] = (h[i-1] * base + (s[i]-'a'+1)) % mod;
    }

    // ví d?: hash do?n [l, r]
    cout << getHash(1, 3) << "\n";
}
