#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;
const int mod = 1e9+7;
int n, m;
vector <int> a[100004];
int vis[100005];

void solve(){
	int n, m;
	cin >> n >> m;
	
	int sum = 0;
	int tmp = 1;
	for (int i = 1; i <= n; i ++ ){
		a[i].assign(m+1, 0);
		
		for (int j = 1; j <= m; j ++ ){
			tmp ++;
			int u = 1;
			for (int h = 1; h < j; h ++ )
				if (__gcd(h, j) == 1){
					vis[a[i][h]] = tmp; 
				}
			for (int h = 1; h < i; h ++ )
				if (__gcd(h, i) == 1){
					vis[a[h][j]] = tmp;
				}
			
			while(vis[u] == tmp) u ++;
			a[i][j] = u;			
			sum += u;
			if (sum >= mod) sum -= mod;
		}		
	}
	cout << sum <<endl;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("MATRIX.inp", "r", stdin);
	freopen("MATRIX.out", "w", stdout);
	solve();

}



