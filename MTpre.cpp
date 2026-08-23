#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define iii pair<int, pair<int, int> >
#define f1(i,n) for(int i=1;i<=n;++i)
#define f0(i,n) for(int i=0;i<n;++i)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT ""
#define el "\n"
#define miti pair<ll,ll>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,popcnt")
//#pragma GCC optimize("Ofast,unroll-loops,inline")
template<class T> bool maximize(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> bool minimize(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 1e9+7;
const int mod = 998244353;
const int N = 2e5+10;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,m,k;
int x1[N], x2[N], y2[N], y3[N];
char tn[N];
ii row[N*2], col[N*2];
int sz1[N], sz2[N];
int he[N], to[N], nxt[N], cnt;
int deg[N];
int q[N],ql,qr;
int ans[N], szl;
void add(int u, int v){
	cnt++;
	to[cnt]=v;
	nxt[cnt]=he[u];
	he[u]=cnt;
	deg[v]++;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	cin >> n >> m >> k;
	for(int i=1;i<=k;i++){
		cin >> x1[i] >> y3[i] >> x2[i] >> y2[i];
		if(x1[i]>x2[i]) tn[i]='U';
		else if(x1[i]<x2[i]) tn[i]='D';
		else if(y3[i]<y2[i]) tn[i]='R';
		else tn[i]='R';
		if(x1[i]==x2[i]){
			int r=x1[i], t1=min(x1[i],x2[i]), t2=max(x1[i], x2[i]);
			for(int t=t1;t<=t2;t++){
				sz1[r]++; sz2[r]++;
				row[t*2+sz1[t]-1]={t,i};
				col[t*2+sz2[t]-1]={r,i};
			}
		}
	}
}
//100077958169269
//iloveMT


