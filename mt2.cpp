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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a,n) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK "SOLPLAY"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt")
//#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 1e9+7;
const int mod = 998244353;
const int N = 1e6+10;
const ll INF = 1e18;
//--------------------------------------------------
int n,p;
int u[10],r[10], c[10], f[10];
int path[N];

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> p;
	FOR(i,1,9) c[i]=0;
	FOR(i,1,n){
		int x; cin >> x;
		c[x]++;
	} 
	FOR(t,1,9){
		if(c[t]==0) continue;
        FOR(i,1,9) f[i] = 2*c[i] + (p==i) - (t==i);
        bool valid = true;
        u[1] = f[1];
        if(u[1] < 0) valid = false;
        FOR(i,2,8){
            u[i] = f[i] - u[i-1];
            if(u[i] < 0) valid = false;
        }
        if(!valid) continue;
        if(u[8] != f[9]) continue;
        long long ss = 0;
        FOR(i,1,8) ss += u[i];
        if(ss != n) continue;
        FOR(i,1,8) r[i] = u[i];
        stack<int> st;
        int cnt = 0;
        st.push(p);
        while(!st.empty()){
            int v = st.top();
            if(v <= 8 && r[v] > 0){
                r[v]--;
                st.push(v+1);
            } else if(v >= 2 && r[v-1] > 0){
                r[v-1]--;
                st.push(v-1);
            } else {
                path[++cnt] = v;
                st.pop();
            }
        }
        if(cnt != n+1) continue;
        for(int i = 1; i <= cnt/2; ++i){
            int tmp = path[i];
            path[i] = path[cnt - i + 1];
            path[cnt - i + 1] = tmp;
        }
        if(path[1] != p) continue;
        int pos[10]; FOR(i,1,9) pos[i]=0;
        for(int i=2;i<=n+1;i++) pos[path[i]]++;
        bool ch = true;
        FOR(i,1,9) if(pos[i] != c[i]) ch = false;
        if(!ch) continue;
        FORD(i,n+1,2){
            cout << path[i]<<" ";
        }
        cout << '\n';
        return 0;
	}
	cout << -1;
}
//100077958169269
//iloveMT



