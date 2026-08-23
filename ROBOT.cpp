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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
//#define sum(a) accumulate(a+1,a+n+1,0ll)
#define All(x) x.begin(),x.end()
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK ""
#define vt vector
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
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
//--------------------------------------------------
struct Mn{
	int r,c,d;
};
struct Tf{
	int r,c;char d;
};
vt<Mn> V;
vt<Tf> H;
vt<int> R,C;
int n,m,k;
int BIT[N], cnt[N],M;
void upd(int i, int val){
	for(;i<=M;i+=i&-i) BIT[i]+=val;
}
int sum(int i){
	int res=0;
	for(;i;i-=i&-i) res+=BIT[i];
	return res;
}
int get(int x){
	int i=upper_bound(All(C),x)-C.begin();
	return sum(i);
}
bool cmp1(Mn x, Mn y){
	return x.r<y.r;
}
bool cmp2(Tf x, Tf y){
	return x.r<y.r;
}
//--------------------------------------------------
int32_t main(){
	faster;
//	freopen(TASK".inp","r",stdin);
//	freopen(TASK".out","w",stdout);
	cin >> n >> m >> k;
	R.pb(1);R.pb(n+1);
	FOR(i,1,k){
		int x,y; char d; cin >> x >> y >> d;
		if(d=='N'){
			V.pb({x,y,1});
			V.pb({n+1,y,-1});
			C.pb(y);
			R.pb(x);
			R.pb(n+1);
		}
		else if(d=='S'){
			V.pb({1,y,1});
			V.pb({x+1,y,-1});
			C.pb(y);
			R.pb(1);
			R.pb(x+1);
		}
		else{
			H.pb({x,y,d});
			R.pb(x);
		}
	}
	sort(All(C)); C.erase(unique(All(C)),C.end());
	sort(All(R)); R.erase(unique(All(R)),R.end());
	sort(All(V),cmp1);
	sort(All(H), cmp2);
	M=C.size();
	FOR(i,1,M) BIT[i]=cnt[i]=0;
	int mt=0, pre=0;
	int c=0,e=0,h=0;
	for(int i : R){
		mt+=c*(i-pre-1);
		while(e<V.size() && V[e].r==i){
			int id=lower_bound(All(C),V[e].c)-C.begin()+1;
			if(V[e].d==1){
				if(++cnt[id]==1) upd(id,1),++c;
			}
			else if(--cnt[id]==0) upd(id,-1),--c;
			++e;
		}
		if(i<=n){
			int l=-1,r=-1;
			while(h<H.size() && H[h].r==i){
				if(H[h].d=='W') maximize(l, H[h].c);
				else r=(r<0 ? H[h].c : min(r,H[h].c));
				++h;
			}
			if(l<0 && r<0) mt+=c;
			else if(l<0) mt+=m-r+get(r-1)+1;
			else if(r<0) mt+=l+c-get(l);
			else{
				if(r<=l+1) mt+=m;
				else mt+=l+m-r-get(l)-get(r-1)+1;
			}
		}
		pre=i;
	}
	cout << mt;
}
//100077958169269
//iloveMT



