#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

int n, d;
int a[2005];

void input(){
	cin >> n >> d;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
}
int ht = 0;
int dp[2][2005][2005];
int dq(int l, int r, int _d){
	ht ++;
	if (l >= r) return 0;
	if (dp[_d][l][r] != -1) return dp[_d][l][r];
	int sum = 1;
	int Max = (_d == 1 ? a[l] + a[r] : a[l] + a[r] + d);
	int Min = (_d == 1 ? a[l] + a[r] - d : a[l] + a[r]);
	for (int L = l + 1, R = r - 1; L < R; L ++ ){
		while(L < R && a[L] + a[R] > Max) R --;
		if (L < R && a[L] + a[R] >= Min){
			sum += dq(L, R, (a[L] + a[R] != Min));
			return dp[_d][l][r] = sum;
		}
	}
	return dp[_d][l][r]= sum;
}
void solve(){
	memset(dp, -1, sizeof dp);
	int ans = 0;
	for (int i = 1; i <= n; i ++ )
	for (int i = 1; i <= n; i ++ )
		for (int j = i + 1; j <= n; j ++ ){
			ans = max({ans, dq(i, j, 0), dq(i, j, 1)});
		}
	cout << ans<<endl;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("PAIR.INP", "r", stdin);
	freopen("PAIR.OUT", "w", stdout);
	input();
	sort(a + 1, a + n + 1);
//	if (n <= 200){
//		sub4::solve();
//		return 0;
//	}
	solve();
	
}



