#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1005;
mt19937 rng64(chrono::steady_clock::now().time_since_epoch().count());
int a[maxn][maxn], res[maxn];
int n,k;
bool cmp(int x, int y){
	if(x==y) return false;
	if(a[x][y]!=0) return a[x][y]==1;
	cout <<"? "<<x<<" "<<y<<endl;
	int ans; cin >> ans;
	if(ans==x){
		a[x][y]=1;
		a[y][x]=-1;
		return true;
	}
	a[y][x]=1;
	a[x][y]=-1;
	return false;
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> k;
	for(int i=1;i<=n;i++) res[i]=i;
	if(k==n){
		cout <<"! 1 1"<<endl;
		for(int i=1;i<=k;i++) cout << res[i]<<(i==k ? "" : " ");
		cout << endl;
		return 0;
	}
	else if(k==1){
		int mx=res[1];
		for(int i=2;i<=n;i++) if(cmp(res[i],mx)) mx=res[i];
		res[1]=mx;
	}
	else{
		shuffle(res+1,res+n+1,rng64)
		nth_element(res+1,res+k, res+n+1, cmp);
	}
	cout <<"! 1 1"<<endl;
	for(int i=1;i<=k;i++) cout << res[i]<<(i==k ? "" : " ");
	cout << endl;
	return 0;
}
//luv


