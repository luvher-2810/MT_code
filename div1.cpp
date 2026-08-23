#include <bits/stdc++.h>
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int MAX = 1e4;
const int N=1e4+5;
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
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    int t; cin >> t;
	while(t--){
		int n,m,k; cin >> n >> m >> k;
		if(k>min(n,m)){
			cout << 0 <<"\n";
			continue; 
		}
		int mt=n+m;
		int xx=nCk(mt,k), zz=nCk(mt,k-1);
		int ans=(xx-zz+MOD)%MOD;
		cout << ans<<'\n';
	}
}

//i love rainy girl

