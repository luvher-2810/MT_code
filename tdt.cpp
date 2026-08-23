#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task "LABS"
const int MOD = 1e9+7;
const int maxn = 1e6+2;
const ll INF = 1e18;
int n,q;
int a[maxn];
struct Node{
	ll x1,x2,y1,y2;
	Node() {
		x1=x2=-INF;
		y1=y2=INF;
	}
};
struct IT{
	Node st[4*maxn];
	Node merge(Node a, Node b){
		Node res;
		ll x[4]={a.x1,a.x2,b.x1,b.x2};
		ll y[4]={a.y1,a.y2,b.y1,b.y2};
		for(int i=0;i<=3;i++){
			if(x[i]>res.x1) res.x2=res.x1,res.x1=x[i];
			else if(x[i]>res.x2) res.x2=x[i];
			if(y[i]<res.y1) res.y2=res.y1,res.y1=y[i];
			else if(x[i]>res.y2) res.y2=y[i];	
		}
		return res;
	}
	void build(int id, int l, int r){
		if(l==r){
			st[id].x1=st[id].y1=a[l];
			return;
		}
		int mid=(l+r)/2;
		build(id*2,l,mid);
		build(id*2+1,mid+1,r);
		st[id]=merge(st[id*2], st[id*2+1]);
	}
	Node get(int id, int l, int r, int u, int v){
		if(u<=l && r<=v) return st[id];
		int mid=(l+r)/2;
		if(v<=mid) return get(id*2,l,mid,u,v);
		if(u>mid) return get(id*2+1,mid+1,r,u,v);
		return merge(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
	}
} seg;
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	if(fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	seg.build(1,1,n);
	cin >> q;
	while(q--){
		int l,r; cin >> l >> r;
		Node ans = seg.get(1,1,n,l,r);
		cout << max(ans.x1*ans.x2, ans.y1*ans.y2) <<"\n";
	}
	return 0;
}


