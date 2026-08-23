#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e5+2;
const int INF = 1e18;
const int NEG = -1e17;
int n,q;
int a[4][maxn], b[4][maxn], A[maxn], B[maxn],f[maxn];
int mn[4*maxn], mx[4*maxn], lz[4*maxn];
vector<int> X[maxn], Y[maxn];
int K[maxn];
void build(int id, int l, int r){
	mn[id]=INF;
	mx[id]=lz[id]=NEG;
	if(l==r) return;
	int mid=(l+r)/2;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
}
void apply(int id, int x){
	if(mn[id]==INF) return;
	mx[id]=max(mx[id],x-mn[id]);
	lz[id]=max(lz[id],x);
}
void down(int id){
	if(lz[id]!=NEG){
		apply(id*2,lz[id]);
		apply(id*2+1,lz[id]);
		lz[id]=NEG;
	}
}
void up(int id){
	mn[id]=min(mn[id*2], mn[id*2+1]);
	mx[id]=max(mx[id*2], mx[id*2+1]);
}
void upd1(int id, int l, int r, int u, int v, int x){
	if(l==r){
		mn[id]=v;
		mx[id]=x;
		return;
	}
	down(id);
	int mid=(l+r)/2;
	if(u<=mid) upd1(id*2,l,mid,u,v,x);
	else upd1(id*2+1,mid+1,r,u,v,x);
	up(id);
}
void upd2(int id, int l, int r, int x){
	if(l==r){
		mn[id]=INF;
		mx[id]=NEG;
		return;
	}
	down(id);
	int mid=(l+r)/2;
	if(x<=mid) upd2(id*2,l,mid,x);
	else upd2(id*2+1,mid+1,r,x);
	up(id);
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=n;j++){
			cin >> a[i][j];
			b[i][j]=b[i][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		A[i]=b[1][i]-b[2][i-1];
		B[i]=b[2][i]-b[3][i-1];
	}	
	for(int i=1;i<=q;i++){
		int l,r; cin >> l >> r >> K[i];
		X[l].push_back(i);
		Y[r].push_back(i);
	}
	build(1,1,q);
	int ans=NEG;
	for(int i=1;i<=n+1;i++){
		if(i-2>=1) for(int it : Y[i-2]) upd2(1,1,q,it);
		if(i-1>=1) for(int it : X[i-1]) upd1(1,1,q,it,K[it],f[i-1]-K[it]);
		if(i-1>=1 && i-1<=n){
			int tmp=mx[1];
			if(tmp>(NEG/2)) ans=max(ans,tmp+B[i-1]);
		}
		if(i<=n) f[i]=max(A[i],mx[1]);
		else f[i]=mx[1];
		if(f[i]>(NEG/2)) apply(1,f[i]);
	}
	cout << ans+b[3][n];
	return 0;
}
//luv


