#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;
const int mod = 1e9 + 7;
int n, b;
int a[2005];
int dp[2005][2005];
int g[2005][2005];
void input(){
	cin >> n >> b;
	
	dp[0][0] = 1;
	for (int i = 1; i <= b; i ++ ){
		g[0][i] = g[0][i - 1] + dp[0][i];
		if (g[0][i] >= mod) g[0][i] -= mod;
	}
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
		
		if (a[i] == -1){
			for (int j = 0; j <= min(b, i - 1); j ++ )
				dp[i][j] = dp[i - 1][j];
			for (int j = 1; j <= min(b, i - 1); j ++ ){
				dp[i][j] = (dp[i][j] + g[i - 1][j - 1] + 1ll*dp[i - 1][j - 1]*(j - 1)) % mod;
			}
			for (int j = 0; j <= b; j ++ ){
				g[i][j] = (j == 0 ? 0 : g[i][j - 1]) + dp[i][j];
				if (g[i][j] >= mod) g[i][j] -= mod;
			}
		}
		else{
			dp[i][a[i]] = g[i - 1][a[i] - 1]; 
			g[i][a[i]] = dp[i][a[i]]; 
			for (int j = a[i] + 1; j <= min(b, i - 1); j ++ ){
				dp[i][j] = dp[i - 1][j - 1];
				g[i][j] = g[i][j - 1] + dp[i][j];
				if (g[i][j] >= mod) g[i][j] -= mod;
 			}
		}
	}
	cout << g[n][b] <<endl;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	freopen("GRAPH.INP", "r", stdin);
	freopen("GRAPH.OUT", "w", stdout);
	input();

}
/*
4 10
-1 -1 1 -1
*/



