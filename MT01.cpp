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
#define MT ""
#define el "\n"
#define miti pair<ll,ll>
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
const int N = 2e5+5;
const ll INF = 1e18;
//----------------------MT---------------------------
int a[77][77], nxt[77];
bool us[77], vis[77];
int ou[N]; 
bool calc1(int i, int j, int m){
	for(int k=1;k<=m;k++) if(a[i][k]!=a[j][k]) return false;
	return true;
}
bool calc2(int i, int j, int m){
	for(int k=1;k<=m;k++) if(a[i][k]!=a[j][k+m]) return false;
	return true;
}
void solve(){
	int n,m; cin >> n >>m;
	f1(i,n) f1(j,m) cin >> a[i][j];
	int sz=0;
	if(n%2==0){
		for(int i=1;i<=n;i++) us[i]=false;
		for(int i=1;i<=n;i++) if(!us[i]){
			int j=i+1;
			while(j<=n && !calc1(i,j,m)) ++j;
			if(j<=n){
				us[i]=us[j]=true;
				for(int k=1;k<=m;k++) ou[sz++]=a[i][k];
			}
		}
	}
	else{
		int h=m/2;
		for(int i=1;i<=n;i++) nxt[i]=-1;
		for(int i=1;i<=n;i++){
			int j=1;
			while(j<=n){
				bool ok=true;
				for(int k=1;k<=h;k++){
					if(a[j][k]!=a[i][k+h]){
						ok=false;
						break;
					}
				}
				if(ok) break;
				++j;
			}
			if(j<=n) nxt[i]=j;
		}
		for(int i=1;i<=n;i++) vis[i]=false;
		int cur=1;
		for(int i=1;i<=n;i++){
			if(vis[cur]) break;
			vis[cur]=true;
			for(int j=1;j<=h;j++) ou[sz++]=a[cur][j];
			cur=nxt[cur];
			if(cur<0) break;
		}
	}
	for(int i=0;i<sz;i++){
		cout << ou[i]<<" ";
	}
	cout << el;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
}
//100077958169269
//iloveMT


