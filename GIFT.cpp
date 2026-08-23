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
#define mp make_pair
#define f1(i,n) for(int i=1;i<=n;++i)
#define f0(i,n) for(int i=0;i<n;++i)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT "GIFT"
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
const int N = 1e5+5;
const int maxn =2e6+5;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,q;
int w[N], s[N];
ii a[N];
int ss[maxn], ww[maxn];
ll ps[maxn], pw[maxn], pp[maxn];
int ptr=0;
struct Node{
	int sg,len;
	ll tt;
} st[4*N];
void build(int id, int l, int r){
	if(l==r){
		int pos=ptr++;
		ss[pos]=a[l].se;
		ww[pos]=a[l].fi;
		ps[pos]=a[l].se;
		pw[pos]=a[l].fi;
		pp[pos]=1ll*a[l].fi*a[l].se;
		st[id].sg=pos;
		st[id].len=1;
		st[id].tt=a[l].fi;
		return;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1, mid+1,r);
	Node &L=st[id<<1], &R=st[id<<1|1], &C=st[id];
	int p=L.sg, q=R.sg, pl=L.len, ql=R.len;
	int stt=ptr, i=0;
	while(i<pl+ql){
		if(p<L.sg+pl && (q>=R.sg + ql || ss[p]<=ss[q])){
			ss[ptr]=ss[p];
			ww[ptr]=ww[p];
			p++;
		}
		else{
			ss[ptr]=ss[q];
			ww[ptr]=ww[q];
			q++;
		}
		ptr++;i++;
	}
	for(int i=0;i<pl+ql;i++){
		if(i==0){
			ps[stt]=ss[stt];
			pw[stt]=ww[stt];
			pp[stt]=1ll*ss[stt]*ww[stt];
		}
		else{
			ps[stt+i]=ps[stt+i-1]+ss[stt+i];
			pw[stt+i]=pw[stt+i-1]+ww[stt+i];
			pp[stt+i]=pp[stt+i-1]+1ll*ss[stt+i]*ww[stt+i];
		}
	}
	C.sg=stt;C.len=pl+ql;C.tt=pw[stt+C.len-1];
}
ii calc(int id, int t){
	Node &C=st[id];
	int l=C.sg, r=C.sg+C.len-1;
	int pos=upper_bound(ss+l,ss+r+1,t)-ss-l;
	ll cnt=(pos>0 ? ps[l+pos-1] : 0) +1ll*(C.len-pos)*t;
	ll wt=(pos>0 ? pp[l+pos-1] : 0) +1ll*(C.tt-(pos>0 ? pw[l+pos-1] : 0))*t;
	return mp(cnt,wt);
}
ll get(int id, int l, int r, ll xx, int t){
	if(xx==0) return 0;
	if(l==r){
		return min((ll)min(a[l].se,t),xx) * a[l].fi;
	}
	int mid=(l+r)>>1;
	ii L =calc(id<<1,t);
	if(L.fi>=xx) return get(id<<1, l,mid,xx,t);
	else return L.se+get(id<<1|1, mid+1,r,xx-L.fi,t);
}
bool ch(ll m, ll k, ll t){
	if(t==0) return true;
	ll nx=1ll*t*k;
	ii tx=calc(1,t);
	if((ll)tx.fi<nx) return false;
	return get(1,1,n,nx,t)<=m;
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> w[i];
	for(int i=1;i<=n;i++) cin >> s[i];
	for(int i=1;i<=n;i++) a[i]=mp(w[i],s[i]);
	sort(a+1,a+n+1);
	build(1,1,n);
	ll sum=0;
	for(int i=1;i<=n;i++) sum+=a[i].se;
	while(q--){
		int type; cin >> type;
		if(type==1){
			ll m,k,t; cin >> m >> k >> t;
			cout << (ch(m,k,t) ? 1 : 0) <<el;
		}
		else{
			ll m,k; cin >> m >> k;
			ll l=0,r=sum/k,mt=0;
			while(l<=r){
				ll mid=(l+r)>>1;
				if(ch(m,k,mid)){
					mt=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			cout << mt << el;
		}
	}
}
//100077958169269
//I love mthuyyyyyy

