#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
const ll INF = 1e18;
int n,k;
int a[maxn], f[maxn], pos[maxn], dp[maxn];
struct IT{
	int st[maxn*4], lz[4*maxn];
	void build(int id, int l, int r){
		lz[id]=0;
		if(l==r){
			st[id]=f[l];
			return;
		}
		int mid=(l+r)/2;
		build(id*2,l,mid);
		build(id*2+1,mid+1,r);
		st[id]=min(st[id*2], st[id*2+1]);
	}
	void push(int id){
		if(lz[id]!=0){
			st[id*2]+=lz[id];
			lz[id*2]+=lz[id];
			st[id*2+1]+=lz[id];
			lz[id*2+1]+=lz[id];
			lz[id]=0;
		}
	}
	void upd(int id, int l, int r, int u, int v,int x){
		if(u<=l && r<=v){
			st[id]+=x;
			lz[id]+=x;
			return;
		}
		push(id);
		int mid=(l+r)/2;
		if(u<=mid) upd(id*2,l, mid, u,v,x);
		if(v>mid) upd(id*2+1,mid+1,r,u,v,x);
		st[id]=min(st[id*2],st[id*2+1]);
	}
	int get(int id, int l, int r, int u, int v){
		if(u<=l && r<=v){
			return st[id];
		}
		push(id);
		int mid=(l+r)/2,res=INF;
		if(u<=mid) res=min(res,get(id*2,l, mid, u,v));
		if(v>mid) res=min(res,get(id*2+1,mid+1,r,u,v));
		return res;
	}
} seg;

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=0;i<=n;i++) f[i]=INF;
	f[0]=0;
	for(int i=1;i<=k;i++){
		seg.build(1,0,n-1);
		fill(pos,pos+n+1,0);
		for(int j=1;j<=n;j++){
			if(pos[a[j]]) seg.upd(1,0,n-1,0,pos[a[j]]-1,j-pos[a[j]]);
			dp[j]=seg.get(1,0,n-1,0,j-1);
			pos[a[j]]=j;
		}	
		for(int j=0;j<=n;j++) f[j]=dp[j];
		f[0]=INF;
	}
	cout << f[n];
	return 0;
}
//luv


