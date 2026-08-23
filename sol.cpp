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
#define vii vector<ii>
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
const int N = 2e5+10;
const ll INF = 1e18;
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
int n;
int a[N], f[N], pos[N], pox[N];
int cnt;
deque<int> mx,mn;
void Add(int i){
	f[a[i]]++;
	if(f[a[i]]==2) ++cnt;
	while(!mn.empty() && a[mn.back()]>=a[i]) mn.pop_back();
	mn.pb(i);
	while(!mx.empty() && a[mx.back()]<=a[i]) mx.pop_back();
	mx.pb(i);
}
void Del(int i){
	if(f[a[i]]==2) --cnt;
	f[a[i]]--;
	if(!mn.empty() && mn.front()==i) mn.pop_front();
	if(!mx.empty() && mx.front()==i) mx.pop_front();
}
void Check(int l, int r){
	if(cnt) return;
	if(a[mx.front()]-a[mn.front()]!=r-1) return;
	minimize(pos[a[mn.front()]], l);
	maximize(pox[a[mn.front()]], l);
}
void hnim(){
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	int mt=0;
	FORD(x, n/2, 1){
		FOR(i,1,n+1){
			f[i]=0;
			pos[i]=INF;
			pox[i]=-INF;
		}
		mn.clear();
		mx.clear();
		cnt=0;
		FOR(i,1,x) Add(i);
		Check(1,x);
		FOR(i,2,n-x+1){
			Del(i-1);
			Add(i+x-1);
			Check(i,x);
		}
		bool ok=false;
		FOR(i,1,n-2*x+1){
			int y=i+x;
			if(pos[i]!=INF && pox[y]!=-1 && pos[i]+x<=pox[y]){
				ok=true;
				break;
			}
			if(pos[y]!=INF && pox[i]!=-1 && pos[y]+x<=pox[i]){
				ok=true;
				break;
			}
		}
		if(ok){
			mt=x;
			break;
		}
	}
	cout << mt <<el;
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	yuht hnim();
}
//100077958169269
//iloveMT





