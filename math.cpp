#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mint __int128
#define task ""
const int MOD = 1e9+7;
const int maxn = 52;
const ll INF = 2e18;
mint calc(mint a, mint b, mint c, mint n){
	a-=n; b-=n; c-=n;
	return a*a+b*b+c*c;
}
ll n;
mint A[maxn], B[maxn], C[maxn];
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n;
	A[0]=0;B[0]=C[0]=1;
	A[1]=3; B[1]=4; C[1]=5;
	mint res=-1;
	ll a=0, b=0, c=0,m=0;
	for(int i=2;i<50;i++){
		A[i]=6*A[i-1]-A[i-2]+2;
		B[i]=6*B[i-1]-B[i-2]-2;
		C[i]=6*C[i-1]-C[i-2];
		m=i;
		if(C[i]>INF) break;
	}
	for(int i=0;i<=m;i++){
		mint u=A[i], v=B[i], w=C[i];
		mint d=n*(u+v+w)/(2*w*w);
		if(d>=0){
			mint cur=calc(d*u,d*v,d*w,n);
			if(res==-1 || cur < res){
				res=cur;
				a=(ll)(d*u);
				b=(ll)(d*v);	
				c=(ll)(d*w);
			}
		}
		d++;
		mint tmp=calc(d*u,d*v,d*w,n);
		if(res==-1 || tmp < res){
			res=tmp;
			a=(ll)(d*u);
			b=(ll)(d*v);	
			c=(ll)(d*w);
		}
	}
	cout << a<<" "<<b<<" "<<c;
	return 0;
}
//luv


