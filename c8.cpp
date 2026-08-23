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
#define vt vector<ii>
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
//--------------------------------------------------
int ask(int x, char c){
	cout<< c<<" "<<x<<endl<<flush;
	int res; cin >> res;
	if(res==-1) exit(0);
	return res;
}
void hnim(){
	int n; cin >> n;
	cout << 0<<endl<<flush;
	int sz=ask(0,'I');
	if(sz==1){
		int c=0;
		REP(i,n){
			int x=MASK(i), xx=ask(x,'I');
			if(maximize(sz,xx)) c|=x;
		}
		cout <<"A 1 "<<c<<endl<<flush;
		return;
	}
	int c=0;
	FORD(i,n-1,0) if(ask(c+MASK(i),'Q')>0) c|=MASK(i);
	if(c==MASK(n)-1){
		int xx=ask(1,'I');
		if(xx==2) cout <<"A 2 "<<c<<endl<<flush;
		else cout <<"A 3 "<<c<<endl<<flush;
	}
	else{
		int q=1;
		while(c&q) q<<=1;
		int x1=ask(q,'I'), x2=ask(c|q, 'I');
		if(x1==x2) cout <<"A 2 "<<c<<endl<<flush;
		else cout <<"A 3 "<<c<<endl<<flush;
	}
}

//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	yuht hnim();
}




