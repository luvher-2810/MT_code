#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
int n;
int a[maxn];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=n;i++){
		if(a[i]<0 || (abs(a[i+1]-a[i])!=1 && i<n)){
			cout << -1 <<"\n";
			return 0;
		}
	}
	bool ok1=true, ok2=true;
	for(int i=1;i<n;i++){
		if(a[i+1]-a[i]!=1) ok1=false;
		if(a[i+1]-a[i]!=-1) ok2=false;
	}
	vector<int> ans;
	if(ok1){
		if(a[1]==0) ans.push_back(1);
		else if(a[1]>1){
			ans.push_back(n+1);
			ans.push_back(n+a[1]);
		}
	}
	else if(ok2){
		if(a[n]==0) ans.push_back(n);
		else ans.push_back(n+a[n]);
	}
	else{
		int j=-1;
		for(int i=2;i<n;i++){
			if((a[i]>a[i-1] && a[i]>a[i+1]) || (a[i]<a[i-1] && a[i]<a[i+1])){
				j=i;
				break;
			}
		}
		if(j!=-1){
			ans.push_back(j);
			ans.push_back(a[j]);
			if(abs(abs(1-j)-a[j])!=a[1]) ans.push_back(a[j]);
		}
	}
	cout << ans.size()<<"\n";
	for(int it : ans) cout << it <<" ";
	return 0;
}
//luv


