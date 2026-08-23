#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

int W, H, n, m, q;

struct rec{
	int x, y, u, v;
	rec(int _x = 0, int _y = 0, int _u = 0, int _v = 0){
		x = _x; y = _y; u = _u; v = _v;
	}
	bool isContain(rec other){
		return x < other.x && other.u < u && y < other.y && other.v < v; 
	}
	
	ll cal(){
		return 1ll*(u-x)*(v-y);
	}
};

rec r[25];
int x[4], y[4];

void solve(){
	cin >> W >> H >> n >> m >> q;
	
	for (int i = 1; i <= n; i ++ ){
		cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2] >> x[3] >> y[3];
		int X = min({x[0], x[1], x[2], x[3]});
		int U = max({x[0], x[1], x[2], x[3]});
		int Y = min({y[0], y[1], y[2], y[3]});
		int V = max({y[0], y[1], y[2], y[3]});
		r[i] = rec(X, Y, U, V);
	}
	
	while(q -- ){
		int x, y;
		cin >> x >> y;
		rec Pick(0, 0, W, H);
		for (int i = 1; i <= n; i ++ )
			if (r[i].isContain(rec(x, y, x, y)) && Pick.isContain(r[i]))
				Pick = r[i];
		
		ll sum = Pick.cal();
		for (int i = 1; i <= n; i ++ )
			if (Pick.isContain(r[i])){
				bool check = 0;
				for (int j = 1; j <= n; j ++ )
					if (r[j].cal() != Pick.cal() && r[j].isContain(r[i])){
						check = 1;
						break;
					}
				if (check == 0) sum -= r[i].cal();
			}
		cout << sum <<endl;
	}
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	freopen("PAINT.INP", "r", stdin);
	freopen("PAINT.OUT", "w", stdout);
	solve();

}
/*
100 100 2 4 2
1 1 1 10 10 10 10 1
4 4 4 6 6 6 6 4

9 9
5 5
*/



