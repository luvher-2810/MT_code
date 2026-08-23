#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
#define MT "CONSO"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
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
const int MAX = 1e7;
const ll INF = 1e18;
//----------------------MT---------------------------
void solve(){
	int n; cin >> n;
	bool ok=false;
	int mt=0;
	for(int i=1;i<=n;i++){
		mt=(mt*10+1)%n;
		int g=__gcd(mt,n), m=n/g;
		cout <<mt<<" "<< i <<" "<<g<<" "<<m<<el;
		if(m<=9){
			cout << string(i,char('0'+m))<<el;
			ok=true;
			break;
		}
	}
	if(!ok) cout << -1 << el;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
}
//I love mthuyyyyyy
//You are lucy, I am luvher, we are a couple
//hihi

