#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
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
#define MT "LIGHT"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
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
const int maxn=1e5+10;
const int N = 670;
const int P = 500;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,q,x,y;
int a[N],p1[N],p2[N];
int ql[maxn],qr[maxn],ans[maxn];
int id[N][maxn], cnt[N];
int d1[P], d2[P],n0[P],n1[P],n2[P];
int cxt=0;
int dist[N][N];
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen("light.inp","r",stdin);
	freopen("light.out","w",stdout);
	cin >> n >> q >> x >> y;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		p1[i]=p1[i-1]+(a[i]==1);
		p2[i]=p2[i-1]+(a[i]==2);
	}
	
	for(int i=0;i<q;i++){
		cin >> ql[i] >> qr[i];
		int len=qr[i]-ql[i]+1;
		id[len][cnt[len]++]=i;
	}
	for(int i=0;i<=x;i++){
		for(int j=0;j<=x-i;j++){
			int kk=x-i-j;
			for(int c=0;c<=y;c++){
				for(int r=0;r<=y-c;r++){
					int kz=y-c-r;
					d1[cxt]=j+r-i-kz;
					d2[cxt]=kk+kz-j-c;
					n0[cxt]=i+c;
					n1[cxt]=j+r;
					n2[cxt]=kk+kz;
					cxt++;
				}
			}
		}
	}
	for(int len=1;len<=n;len++){
		if(!cnt[len]) continue;
		for(int i=0;i<=len;i++) for(int j=0;j<=len;j++) dist[i][j]=-1;
		queue<ii> q;
		dist[0][0]=0;
		q.push({0,0});
		while(!q.empty()){
			int c1=q.front().fi, c2=q.front().se;
			q.pop();
			int cur=dist[c1][c2];
			for(int k=0;k<cxt;k++){
				int p1=c1+d1[k],p2=c2+d2[k];
				if(p1<0 || p2<0 || p1+p2>len) continue;
				int p0=len-p1-p2;
				if(p0<0) continue;
				if(n0[k]>p0 || n1[k]>p1 || n2[k]>p2) continue;
				if(dist[p1][p2]==-1){
					dist[p1][p2]=cur+1;
					q.push({p1,p2});
				}
			}
		}
		for(int t=0;t<cnt[len];t++){
			int ix=id[len][t], l=ql[ix], r=qr[ix];
			int c1=p1[r]-p1[l-1], c2=p2[r]-p2[l-1];
			ans[ix]=dist[c1][c2]; 
		}
	}
	for(int i=0;i<q;i++) cout << ans[i]<<el;
}
//100077958169269
//I love mthuyyyyyy



