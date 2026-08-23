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
const int N = 1e6+10;
const ll INF = 1e18;
//----------------------MT---------------------------
struct seg{
	ll l,r,w;
};
struct node{
	ll lz,t;
};
bool cmp(seg a, seg b){
	return a.r<b.r;
}
int n,m,mt;
seg a[N];
node st[4*N];	
void app(ll id){
	ll k=st[id].lz;
	st[id*2].lz+=k;
	st[id*2].t+=k;
	st[id*2+1].lz+=k;
	st[id*2+1].t+=k;
	st[id].lz=0;
}
void upd(int id, int l, int r, int u, int v, int val){
	if(r<u || l>v) return;
	if(u<=l && r<=v){
		st[id].t+=val;
		st[id].lz+=val;
		return;
	}
	app(id);
	int mid=(l+r)/2;
	upd(id*2,l,mid,u,v,val);
	upd(id*2+1,mid+1,r,u,v,val);
	st[id].t=max(st[id*2].t, st[id*2+1].t);
	return;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	#define MT "SSEQ"
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i].l >> a[i].r>>a[i].w;
		maximize(m,a[i].r);
	}
	mt=-INF;
	sort(a+1,a+n+1,cmp);
	a[n+1].r=INF;
	for(int i=1;i<=n;i++){
		upd(1,1,m,1,a[i].l,a[i].w);
		if(i==n || a[i].r!=a[i+1].r) maximize(mt,st[1].t);
	}
	cout << mt;
}
//100077958169269
//Toi yeu Minh Thuy


