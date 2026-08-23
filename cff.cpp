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
const int N = 2e5+10;
const ll INF = 1e18;
//----------------------MT---------------------------
struct Query{
	int l,r;
} qs[N];
int ans[N], dc[2][N], dl[2][N];
//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	int t; cin >> t;
	while(t--){
		int n,q; cin >> n >> q;
		for(int i=1;i<=n;i++) ans[i]=0;
		for(int i=1;i<=q;i++) cin >> qs[i].l >> qs[i].r;
		for(int i=0;i<19;i++){
			int mask=MASK(i+1), hf=MASK(i), lim=min(mask, n+1);
			int term=hf;
			for(int j=0;j<lim;j++){
				int sz=(n-j)/mask+3;
				for(int xx=0;xx<sz;xx++) dc[0][xx]=dl[0][xx]=0;
				for(int xx=1;xx<=q;xx++){
					int l=qs[xx].l, r=qs[xx].r;
					int tg=(l+hf-1) & (mask-1);
					if(tg != j) continue;
					int st=l, rm=l&(mask-1);
					if(rm<=tg) st+=tg-rm;
					else st+=mask+tg-rm;
					if(st>r) continue;
					int cnt=(r-st)/mask,end=st+cnt*mask;
					int idx1=st/mask, idx2=end/mask;
					int val=-(l-1)*term;
					dc[0][idx1]+=val; dl[0][idx1]+=term;
					dc[0][idx2+1]-=val; dl[0][idx2+1]-=term; 		
				}
				int c1=0, c2=0;
				for(int k=0;;k++){
					c1+=dc[0][k]; c2+=dl[0][k];
					if(c1==0 && c2==0) continue;
					int idx=k*mask+j;
					if(idx>n) break;
					if(idx>=1) ans[idx]+=c1+c2*idx;
				}	
			}
			
		}
		for(int i=1;i<=n;i++) cout << ans[i]<<" ";
		cout << el;
	}
}
//100077958169269
//I love mthuyyyyyy



