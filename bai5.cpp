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
#define MT ""
#define el "\n"
#define mity pair<ll,ll>
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
const int N = 1e6+10;
const ll INF = 1e18;
int n,m,cnt;
int w[N],h[N],t[4*N],nxt[4*N],cl[N];
mity cmp[N];
bitset<1000005> tmp,dp;
void add(int u, int v){
	t[++cnt]=v;
	nxt[cnt]=h[u];
	h[u]=cnt;
}
bool bfs(int s, int &s0, int &s1){
	queue<int> q;
	q.push(s);
	cl[s]=0;
	s0=s1=0;
	while(q.size()){
		int u=q.front();q.pop();
		if(cl[u]==0) s0+=w[u];
		else s1+=w[u];
		for(int k=h[u];k;k=nxt[k]){
			int v=t[k];
			if(cl[v]==-1){
				cl[v]=cl[u]^1;
				q.push(v);
			}
			else if(cl[v]==cl[u]) return false;
		}
	}
	return true;
}
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--){
		cin >> n >> m;
		for(int i=1;i<=n;i++) cin >> w[i];
		cnt=0;
		for(int i=1;i<=n;i++){
			h[i]=0;
			cl[i]=-1;
		}
		int tl=sum(w),cz=0;
		for(int i=1;i<=m;i++){
			int x,y; cin >> x >> y;
			add(x,y);add(y,x);
		}
		for(int i=1;i<=n;i++){
			if(cl[i]==-1){
				int s0,s1;
				if(!bfs(i, s0,s1)){
					cout <<0;
					continue;
				}
				cmp[++cz]={s0,s1};
			}
		}
		dp.reset();
		dp[0]=1;
		for(int i=1;i<=cz;i++){
			tmp.reset();
			tmp |= (dp << cmp[i].fi);
			tmp |= (dp << cmp[i].se);
			dp=tmp;
		}
		cout << dp.count();
	}
}
//100077958169269
//iloveMT


