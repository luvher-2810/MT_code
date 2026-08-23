#include <bits/stdc++.h>
#define ll long long
#define task ""
const int MOD = 1e9+7;
const int MAX = 2e6;
const int N=2e6+5;
using namespace std;
ll frac[N],inv[N];
ll pw(ll x, ll y){
    ll ans = 1;
    ll mul = x;
    while(y > 0){
        if(y & 1) {
            ans = 1ll * ans * mul % MOD;
        }
        mul = 1ll * mul * mul % MOD;
        y >>= 1;
    }
    return ans;
} 
void solve(){
    frac[0] = 1;
    for(int i = 1; i <= MAX; i++) {
        frac[i] = 1ll * frac[i-1] * i % MOD;
    }
    inv[MAX] = pw(frac[MAX], MOD-2);
    for(int i = MAX; i > 0; i--) {
        inv[i-1] = 1ll * inv[i] * i % MOD;
    }
}
ll nCk(ll n, ll k){
    return 1ll * frac[n] * inv[k] % MOD * inv[n-k] % MOD;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    int n, m;
    cin >> n >> m;
    cout << nCk(n+m-2, n-1);
}

//i love rainy girl

