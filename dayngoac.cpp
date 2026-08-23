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
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
//--------------------------------------------------
string s;
struct Node{
	int x,y,ans;
};
struct IT{
	Node st[N*4];
	Node merge(Node a, Node b){
		int t=min(a.x, b.y);
		Node res;
		res.x=a.x+b.x-t;
		res.y=a.y+b.y-t;
		res.ans=a.ans+b.ans+t;
		return res;
	}
	void build(int id, int l, int r){
		if(l==r){
			if(s[l]=='(') st[id]={1,0,0};
			else st[id]={0,1,0};
			return;
		}
		int mid=(l+r)/2;
		build(id*2,l,mid);
		build(id*2+1, mid+1, r);
		st[id]=merge(st[id*2], st[id*2+1]);
	}
	Node get(int id, int l, int r, int u, int v){
		if(l>v || r<u) return {0,0,0};
		if(u<=l && r<=v) return st[id];
		int mid=(l+r)/2;
		Node x=get(id*2,l,mid,u,v);
		Node y=get(id*2+1, mid+1, r, u,v);
		return merge(x,y);
	}
} seg;
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
//	yuht hnim();
	cin >> s;
	s="#"+s;
	int n=s.size()-1;
	seg.build(1,1,n);
	int q;cin >> q;
	while(q--){
		int l,r; cin >> l >> r;
		Node mt=seg.get(1,1,n,l,r);
		cout << mt.ans*2<<el;
	}
}
//100077958169269
//iloveMT




