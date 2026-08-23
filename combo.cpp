#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define task "combo"
const int MOD = 1e9+7;
const int maxn = 1e6+2;
int n,q;
int a[maxn], pos[maxn];
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen(task".inp","r",stdin);
	freopen(task".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i];
	while(q--){
		int type,x,y; cin >> type >> x >> y;
		if(type==1) a[x]=y;
		else{
			int ans=0;
			for(int i=x;i<=y;i++){
				int j=lower_bound(pos,pos+ans,a[i])-pos;
				pos[j]=a[i];
				if(j==ans) ++ans;
			}
			cout << ans <<"\n";
		}
	}
	return 0;
}
//luv


