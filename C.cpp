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
#define f1(i,n) for(int i=1;i<=n;++i)
#define f0(i,n) for(int i=0;i<n;++i)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
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

const int MOD = 1e9+7;
const int mod = 998244353;
const int N = 2e5+10;
const ll INF = 1e18;

int n, k;
ll a[N], b[N], c[N], d[N];

struct Node{
    ll sum;
    int x1, x2;
    bool operator < (const Node &other) const {
        return sum < other.sum;
    }
};

int32_t main(){
    faster;

    cin >> n >> k;
    f1(i,n) cin >> a[i];
    f1(i,n) cin >> b[i];
    f1(i,n) cin >> c[i];
    f1(i,n) cin >> d[i];
    sort(a+1, a+n+1, greater<ll>());
    sort(b+1, b+n+1, greater<ll>());
    sort(c+1, c+n+1, greater<ll>());
    sort(d+1, d+n+1, greater<ll>());

    vector<ll> s1, aa, bb;
    priority_queue<Node> pq;

    f1(i, min(k,n)) pq.push({a[i] + b[1], i, 1});

    while(!pq.empty() && s1.size() < k){
        Node cur = pq.top(); pq.pop();
        s1.pb(cur.sum);
        aa.pb(a[cur.x1]);
        bb.pb(b[cur.x2]);
        if(cur.x2 + 1 <= n){
            pq.push({a[cur.x1] + b[cur.x2 + 1], cur.x1, cur.x2 + 1});
        }
    }

    while(!pq.empty()) pq.pop();

    vector<ll> s2, cc, dd;

    f1(i, min(n,k)) pq.push({c[i] + d[1], i, 1});

    while(!pq.empty() && (int)s2.size() < k){
        Node cur = pq.top(); pq.pop();
        s2.pb(cur.sum);
        cc.pb(c[cur.x1]);
        dd.pb(d[cur.x2]);
        if(cur.x2 + 1 <= n){
            pq.push({c[cur.x1] + d[cur.x2 + 1], cur.x1, cur.x2 + 1});
        }
    }

    priority_queue<Node> pq2;

    int sz1 = s1.size();
    int sz2 = s2.size();

    for(int i = 0; i < min(k, sz1); i++){
        pq2.push({s1[i] + s2[0], i, 0});
    }

    ll cnt = 0;

    while(!pq2.empty()){
        Node cur = pq2.top(); pq2.pop();
        cnt++;
        if(cnt == k){
            cout << aa[cur.x1] << " " << bb[cur.x1] << " "<< cc[cur.x2] << " " << dd[cur.x2];
            return 0;
        }
        if(cur.x2 + 1 < sz2){
            pq2.push({s1[cur.x1] + s2[cur.x2 + 1], cur.x1, cur.x2 + 1});
        }
    }

    return 0;
}

