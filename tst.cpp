#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define iii pair<int, pair<int, int> >
#define All(X) X.begin(), X.end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
#define yuht int _; cin >> _; while(_--)
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}

const int MOD = 998244353;
const int mod = 998244353;
const ll INF = 1e18;
const int G = 3;

mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

int mod_pow(int a, ll e){
    ll r = 1, x = a;
    while(e){
        if(e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vt &a, bool invert){
    int n = (int)a.size();

    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        int wlen = mod_pow(G, (MOD - 1) / len);
        if(invert) wlen = mod_pow(wlen, MOD - 2);

        for(int i = 0; i < n; i += len){
            ll w = 1;
            int half = len >> 1;
            for(int j = 0; j < half; j++){
                int u = a[i + j];
                int v = (ll)a[i + j + half] * w % MOD;

                a[i + j] = u + v;
                if(a[i + j] >= MOD) a[i + j] -= MOD;

                a[i + j + half] = u - v;
                if(a[i + j + half] < 0) a[i + j + half] += MOD;

                w = w * wlen % MOD;
            }
        }
    }

    if(invert){
        int inv_n = mod_pow(n, MOD - 2);
        for(int &x : a) x = (ll)x * inv_n % MOD;
    }
}

struct Mat{
    int a, b, c, d;
};

Mat mulM(const Mat &x, const Mat &y){
    Mat z;
    z.a = ((ll)x.a * y.a + (ll)x.b * y.c) % MOD;
    z.b = ((ll)x.a * y.b + (ll)x.b * y.d) % MOD;
    z.c = ((ll)x.c * y.a + (ll)x.d * y.c) % MOD;
    z.d = ((ll)x.c * y.b + (ll)x.d * y.d) % MOD;
    return z;
}

Mat pwM(Mat base, ll e){
    Mat res{1, 0, 0, 1};
    while(e){
        if(e & 1) res = mulM(res, base);
        base = mulM(base, base);
        e >>= 1;
    }
    return res;
}

int calc_one(int A, int B, ll L){
    if(L == 0) return 1;
    if(L == 1) return A;
    Mat M{A, B, 1, 0};
    Mat P = pwM(M, L - 1);
    return ((ll)P.a * A + P.b) % MOD;
}

int32_t main(){
    faster;

    ll n, m;
    cin >> n >> m;

    ll L = n - 1;

    int N = 1;
    while(N <= 4LL * L) N <<= 1;
    if(N == 0) N = 1;

    int w = mod_pow(G, (MOD - 1) / N);
    int iw = mod_pow(w, MOD - 2);

    int shift = mod_pow(w, (2LL * L) % N);

    vt val(N);

    int z = 1, iz = 1;
    int factor = 1;

    FOR(k, 0, N - 1){
        int A = ((ll)z * z + (ll)iz * iz) % MOD;
        int B = (z + iz) % MOD;

        int f = calc_one(A, B, L);
        val[k] = (ll)factor * f % MOD;

        z = (ll)z * w % MOD;
        iz = (ll)iz * iw % MOD;
        factor = (ll)factor * shift % MOD;
    }

    ntt(val, true);

    FOR(y, 1, m){
        ll idx = 2LL * L + (y - 1);
        if(idx >= N) cout << 0 << el;
        else cout << val[idx] << el;
    }

    return 0;
}
