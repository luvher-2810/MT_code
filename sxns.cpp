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
const int N = 18;
const ll INF = 1e18;
//----------------------MT---------------------------
int n,m;
int cnt[512], f[512][N];
int dp[MASK(N)], pre[MASK(N)];

//----------------------MT---------------------------
int32_t main(){
	faster;
//	freopen(MT".inp","r",stdin);
//	freopen(MT".out","w",stdout);
	cin >> n >> m;
	f1(i,n) f1(j,m) {
		int x; cin >> x;
		f[x][++cnt[x]]=i;
	}
	f0(mask, MASK(n)) dp[mask]=-INF;
	dp[0]=0;
	for(int x=1;x<=256;x++){
		if(!cnt[x]) continue;
		f0(mask,MASK(n)) pre[mask]=dp[mask];
		f0(mask,MASK(n)) {
			if(dp[mask]<0) continue;
			for(int i=1;i<=cnt[x];i++){
				int xx=f[x][i]-1;
				if((mask & MASK(xx))==0){
					int zz=mask | MASK(xx);
					maximize(pre[zz],dp[mask]+x);
				}
			}
		}
		f0(mask,MASK(n)) dp[mask]=pre[mask];
	}
	int mt=-INF;
	f0(mask,MASK(n)) maximize(mt, dp[mask]);
	cout << mt;
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

