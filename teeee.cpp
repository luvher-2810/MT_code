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
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MT "PREANDSUF"
#define vt vector<ii>
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
const int N = 1e6+10;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,q;
string s[N];
int pre1[N][26], pre2[N], pre;
int suf1[N][26], suf2[N], suf;
int bit1[26][N], bit2[26][N], bit3[N];
ll ans[N];
vt qr[N];
void add(int bit[], int i, int x){
	for(;i<=n;i+=i&-i) bit[i]+=x;
}
int sum(int bit[], int i){
	int res=0;
	for(;i;i-=i&-i) res+=bit[i];
	return res;
}
int ran(int bit[], int l, int r){
	if(r<l) return 0;
	return sum(bit,r)-sum(bit,l-1);
}
//----------------------MT---------------------------
int32_t main(){
	faster;
	freopen(MT".inp","r",stdin);
	freopen(MT".out","w",stdout);
	cin >> n >> q;
	f1(i,n) cin >> s[i];
	f0(i,N) {
		pre2[i]=0;
		if(i<N) suf2[i]=0;
		f0(k,26) {
			if(i<N) pre1[i][k]=suf1[i][k]=0;
		}
	}
	pre=1;suf=1;
	f1(i,n) {
		int nx=1;
		for(char c : s[i]){
			int k=c-'a';
			if(pre1[nx][k]==0) pre1[nx][k]=++pre;
			nx=pre1[nx][k];
		}
		nx=1;
		for(int j=s[i].size()-1;j>=0;j--){
			int k=s[i][j]-'a';
			if(suf1[nx][k]==0) suf1[nx][k]=++suf;
			nx=suf1[nx][k];
		}
	}
	f1(i,q) {
		int l,r; cin >> l >> r;
		qr[r].pb({l,i});
	}
	f1(i,n) {
		int p=1;
		for(int x=0;x<s[i].size();x++){
			int k=s[i][x]-'a';
			p=pre1[p][k];
			if(x) if(pre2[p]) add(bit1[k], pre2[p],-1);
			pre2[p]=i;
			if(x) add(bit1[k], pre2[p],1);
		}
		int ss=1;
		for(int x=s[i].size()-1,rev=0;x>=0;x--,rev++){
			int k=s[i][x]-'a';
			ss=suf1[ss][k];
			if(suf2[ss]) add(bit3,suf2[ss],-1);
			if(rev) if(suf2[ss]) add(bit2[k], suf2[ss],-1);
			suf2[ss]=i;
			add(bit3,suf2[ss],1);
			if(rev) add(bit2[k], suf2[ss],1);
		}
		for(ii it : qr[i]){
			int l=it.fi, id=it.se, tt=ran(bit3,l,i);
			ll res=0;
			f0(k,26) {
				int rt=pre1[1][k];
				if(rt!=0 && pre2[rt]>=l) res+=tt;
				res+=1ll*ran(bit1[k],l,i)*(tt-ran(bit2[k],l,i));
			}
			ans[id]=res;
		}
	}
	f1(i,q) cout << ans[i]<<el;
}
//I love mthuyyyyyy
//You are lucy, I am luvher, we are a couple


/*Nhung cau ca em diu nhe nhang bay qua giac mo cua em
Chi mot giay thoi nguoi oi cung lam tim em xuyen xao
Nang buong qua khung cua cham vao doi mi van nhu con thuong
Lac vao doi mat cua ai lam cho con tim nho mong

Khi con mua nhe roi voi vang doi tay anh luot qua
Cham vao anh mat bo moi nhe run chang cat nen loi
Anh mang may nhe troi chim vao bau troi muon anh sao
De lai noi day minh em ngan ngo dem dai nho mong

Nhung cau ca em diu nhe nhang bay qua giac mo cua em
Chi mot giay thoi nguoi oi cung lam tim em xuyen xao
Nang buong qua khung cua cham vao doi mi van nhu con thuong
Lac vao doi mat cua ai lam cho con tim nho mong

Chi muon ben anh that gan nhe nhang con gio luot qua
Lan toc em ru may troi diu dang em dung truoc ta
Dat khe len tren tay nguoi nhanh hong cau ca khe buong
Ngay nang cho anh nu cuoi diu dang doi moi khe trao

Chi muon ben anh that gan nhe nhang con gio luot qua
Lan toc em ru may troi diu dang em dung truoc ta
Dat khe len tren tay nguoi nhanh hong cau ca khe buong
Ngay nang cho anh nu cuoi diu dang doi moi khe trao

Em nhu con gio mang thanh am thoi qua tai
Nhu melody anh viet khong suy tu vao ban mai
Ta ngam su troi day tu nhung tia sang nho
Binh yen trong ta mot ngay tron ven khong dang bo

La co em ben doi minh cung phieu vai cau ca
Ta nhu mot dua nhoc ma khong can dung loi sau xa
Dau ra nhung dieu la ki o trong khong gian nay ya
Ngay nao vang em anh nhu mua dong khong mang giay

Nhung cau ca em diu nhe nhang bay qua giac mo cua em
Chi mot giay thoi nguoi oi cung lam tim em xuyen xao
Nang buong qua khung cua cham vao doi mi van nhu con thuong
Lac vao doi mat cua ai lam cho con tim nho mong

Chi muon ben anh that gan nhe nhang con gio luot qua
Lan toc em ru may troi diu dang em dung truoc ta
Dat khe len tren tay nguoi nhanh hong cau ca khe buong
Ngay nang cho anh nu cuoi diu dang doi moi khe trao

Chi muon ben anh that gan nhe nhang con gio luot qua
Lan toc em ru may troi diu dang em dung truoc ta
Dat khe len tren tay nguoi nhanh hong cau ca khe buong
Ngay nang cho anh nu cuoi diu dang doi moi khe trao

Nhung cau ca em diu nhe nhang bay qua giac mo cua em
Chi mot giay thoi nguoi oi cung lam tim em xuyen xao
Nang buong qua khung cua cham vao doi mi van nhu con thuong
Lac vao doi mat cua ai lam cho con tim nho mong*/

