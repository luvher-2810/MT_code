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
#define MT "THREE"
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
const ll INF = 1e18;
//----------------------MT---------------------------
int n,m,q;
int sr[N], sc[N];
miti mp;
struct ps{
	int r,c,w;
};
ps a[N];
int al[13];
int calc(int x){
	if(x<=n) return sr[x];
	return sc[x-n];
}
int sq(int x, int y){
	return (x-1)*n+y;
}
void add(int x){
	int pos=-1;
	for(int i=1;i<7;i++){
		if(calc(x)>calc(al[i])){
			pos=i;
			break;
		}
	}
	if(pos==-1) return;
	for(int i=6;i>pos;i--) al[i]=al[i-1];
	al[pos]=x;
}
int gd(int a, int b){
	if(a<=n && b>n) return mp[sq(a,b-n)];
	if(a>n && b<=n) return mp[sq(b,a-n)];
	return 0;	
}
void sol(){
	int ans=0;
	for(int i=1;i<7;i++){
		for(int j=i+1;j<8;j++){
			for(int k=j+1;k<9;k++){
				int vi=al[i], vj=al[j], vk=al[k];
				if(vi==0 || vj==0 || vk==0) continue;
				if(vi==vj || vj==vk || vk==vi) continue;
				int cur=calc(vi)+calc(vj)+calc(vk)-gd(vi,vj)-gd(vj,vk)-gd(vk,vi);
				maximize(ans,cur);
			}
		}
	}
	cout << ans << el;
}
void solve(){
	mp.clear();
	memset(al,0,sizeof al);
	memset(sr,0,sizeof sr);
	memset(sc,0,sizeof sc);
	cin >> n >> m >> q;
	vt vec;
	for(int i=1;i<=m;i++){
		cin >> a[i].r >> a[i].c >> a[i].w;
		vec.pb(a[i].r);vec.pb(a[i].c);
	}
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	n=vec.size();
	for(int i=1;i<=m;i++){
		a[i].r=lower_bound(vec.begin(),vec.end(),a[i].r)-vec.begin()+1;
		a[i].c=lower_bound(vec.begin(),vec.end(),a[i].c)-vec.begin()+1;
		mp[sq(a[i].r,a[i].c)]=a[i].w;
		sr[a[i].r]+=a[i].w; sc[a[i].c]+=a[i].w;
	}
	for(int i=1;i<=n;i++){
		if(sr[i]) add(i);
		if(sc[i]) add(i+n);
	}
	sol();
	while(q--){
		int t,d; cin >> t >> d;
		mp[sq(a[t].r,a[t].c)]+=d;
		sr[a[t].r]+=d; sc[a[t].c]+=d;
		al[7]=a[t].r;
		al[8]=a[t].c+n;
		sol();
		mp[sq(a[t].r,a[t].c)]-=d;
		sr[a[t].r]-=d;sc[a[t].c]-=d;
	}
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
}
//100077958169269
//Toi yeu Minh Thuy


