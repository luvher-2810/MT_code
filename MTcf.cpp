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
const int N = 1e5+10;
const ll INF = 1e9;
//----------------------MT---------------------------
struct fen{
	int n, b[N];
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++) b[i]=0;
	}
	void add(int i, int v){
		for(;i<=n;i+=i&-i) b[i]+=v;
	}
	int sum(int i){
		int r=0;
		for(;i>0;i-=i&-i) r+=b[i];
		return r;
	}
	int kth(int k){
		int i=0, s=1;
		while((s<<1)<=n) s<<=1;
		for(;s;s>>=1){
			int j=i+s;
			if(j<=n && b[j]<k){
				i=j;
				k-=b[j];
			}
		}
		return i+1;
	}
};
int n, x[N], y[N];
int id[N], idx[N], xs[N], st[N], sz[N];
fen top, bot;
int x1,x2;
bool ok(int k, int &xx, int &yy){
	if(k==0){
		xx=0; yy=0;
		return true;
	}
	if(4*k>n) return false;
	top.init(x1); bot.init(x1);
	for(int i=1;i<=n;i++) bot.add(idx[i],1);
	int up=0;
	for(int i=1;i<=x2;i++){
		int s1=st[i], s2=sz[i];
		for(int j=0;j<s2;j++){
			int u=id[s1+j];
			bot.add(idx[u],-1); top.add(idx[u],1);
			up++;
		}
		int dn=n-up;
		if(up<2*k || dn<2*k) continue;
		int t1=top.kth(k), t2=top.kth(up-k+1);
		int l1=xs[t1]+1, r1=xs[t2];
		int t3=bot.kth(k), t4=bot.kth(dn-k+1);
		int l2=xs[t3]+1, r2=xs[t4];
		maximize(l1,l2); minimize(r1,r2);
		if(l1<=r1){
			if(l1<-INF) l1=-INF;
			if(l1>INF){
				if(r1>INF || r1<-INF) continue;
				l1=r1;
			}
			xx=l1; yy=y[id[st[i]]];
			return true;
		}
	}
	return false;
}
void solve(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> x[i] >> y[i];
		xs[i]=x[i];
	}
	sort(xs+1,xs+n+1);
	x1=unique(xs+1,xs+n+1)-(xs+1);
	for(int i=1;i<=n;i++) idx[i]=lower_bound(xs+1,xs+x1+1, x[i])-xs;
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1,[&](int a,int b){
		if(y[a]!=y[b]) return y[a]>y[b];
		return x[a]<x[b];	
	});
	x2=0;
	for(int i=1;i<=n;){
		int j=i,c=0,p=id[i];
		int yz=y[p];
		while(j<=n && y[id[j]]==yz) j++, c++;
		x2++;
		st[x2]=i;
		sz[x2]=c;
		i=j;
	}
	int l=0, r=n/4, mt=0;
	int xx=0, yy=0;
	while(l<=r){
		int mid=(l+r)/2;
		int z1,z2;
		if(ok(mid, z1,z2)){
			mt=mid;
			xx=z1, yy=z2;
			l=mid+1;
		}
		else r=mid-1;
	}
	cout << mt<<el;
	cout << xx<<" "<<yy<<el;
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


