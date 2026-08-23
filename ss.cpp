#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
void solve(){
	int n,k; string s; cin >> n >> k >> s;
	s=" "+s;
	int ans=0, res=0;
	for(int i=1;i<=2*n;i++) if(s[i]==1){
		int pos=(s[(i+1)%(2*n)]=='0' ? (i+1)%(2*n) : i);
		if(pos&1) ans++;
		else res++;
	}
	cout << res<<" "<<ans<<"\n";
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
//luv

