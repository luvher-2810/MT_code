#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
int n,q;
int a[maxn], pre[maxn];
ll val1[maxn], val2[maxn], b1[505], b2[505];
ll ans[maxn];
vector<pair<int,int>> qr[maxn];
void add(int idx, int v){
	if(idx>n+2 || idx<1) return;
	val1[idx]+=v;
	val2[idx]+=idx*v;
	b1[idx/450]+=v;
	b2[idx/450]+=idx*v;
}
ll solve1(int idx){
	ll sum=0, xx=idx/450;
	for(int i=0;i<xx;i++) sum+=b1[i];
	for(int i=xx*450;i<=idx;i++) sum+=val1[i];
	return sum;
}

ll solve2(int idx){
	ll sum=0, xx=idx/450;
	for(int i=0;i<xx;i++) sum+=b2[i];
	for(int i=xx*450;i<=idx;i++) sum+=val2[i];
	return sum;
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i], pre[i]=a[i]+pre[i-1];
	for(int i=1;i<=q;i++) {
		int l,r; cin >> l >> r;
		qr[r].push_back({l,i});
	}
	for(int i=1;i<=n;i++){
		int mn=min(i,a[i]), x=1;
		while(x<=mn){
			ll val=a[i]/x;
			if(val==0) break;
			ll y=min(mn, a[i]/val);
			int l=i-y+1, r=i-x+1;
			add(l,val*y);
			add(l+1,-1*val*(y+1));
			add(r+1,-1*val*(x-1));
			add(r+2,val*x);
			x=y+1;
		}
		for(pair<int,int> it : qr[i]){
			int l=it.first, id=it.second;
			ll res=1ll*(l+1)*solve1(l)-solve2(l);
			ans[id]=(pre[i]-pre[l-1])-res;
		}
	}
	for(int i=1;i<=q;i++) cout << ans[i]<<"\n";
	return 0;
}
//luv


