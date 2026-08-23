#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task "noel"
const int MOD = 1e9+7;
const int maxn = 1e6+10;
const ll INF = 1e18;
int n,q;
int a[maxn];
int idx[maxn], pos[maxn], mx[maxn], nxt[maxn][19];
ll f[maxn];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen(task".inp","r",stdin);
	freopen(task".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i], pos[i]=n+1;
	idx[n]=pos[a[n]]=n; mx[n]=1;
	for(int i=n-1;i>=1;i--){
		idx[i]=min(idx[i+1],pos[a[i]]-1);
		mx[i]=idx[i]-i+1;
		pos[a[i]]=i;
	}
	for(int i=1;i<=n;i++) nxt[i][0]=i+mx[i];
	for(int i=0;i<=18;i++) nxt[n+1][i]=n+1;
	for(int k=1;k<=18;k++) for(int i=1;i<=n;i++){
		if(nxt[i][k-1]<=n+1) nxt[i][k]=nxt[nxt[i][k-1]][k-1];
		else nxt[i][k]=n+1;
	}
	while(q--){
		int l,r; ll x,y; cin >> l >> r >> x >> y;
		int L=l, ans=0;
		for(int k=18;k>=0;k--) if(nxt[L][k]<=r-95){
			L=nxt[L][k];
			ans+=(1<<k);
		}
		f[r+1]=1;
		for(int j=r;j>=(int)max(l,r-95);j--){
			ll sum=0, xx=j+mx[j];
			if(xx>r+1) xx=r+1;
			for(int k=j+1;k<=xx;k++){
				sum+=f[k];
				if(sum>INF){
					sum=INF;
					break;
				}
			}
			f[j]=sum;
		}
		int X=L, Y=L;
		auto solve=[&](int u, ll &tar) -> int {
			int xx=u+mx[u];
			if(xx>r+1) xx=r+1;
			for(int j=xx;j>=u+1;j--){
				ll ways=(j<max(l,r-95) ? INF : f[j]);
				if(tar<=ways) return j;
				else tar-=ways;
			}
			return -1;
		};
		while(X<=r && Y<=r){
			int x1=solve(X,x), x2=solve(Y,y);
			if(x1==x2 && x1!=-1){
				ans++;
				X=x1;
				Y=x2;
			}
			else break;
		}
		cout << ans << "\n";
	}
	return 0;
}
//luv


