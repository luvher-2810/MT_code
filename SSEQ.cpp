#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

int n;
struct sig{
	int l, r, w;
	sig(){
		l = r = w = 0;
	}
};
sig Q[100005];
bool cmp(sig A, sig B){
	return A.r < B.r;
}

struct s3x{
	struct node{
		ll Max;
		int lz;
		
		node(){
			Max = 0; 
			lz = 0;
		}
		
		void apd(int val){
			Max += val;
			lz += val;
		}
	};
	
	node st[1200005];
	
	void down(int id){
		if (st[id].lz == 0) return;
		st[(id << 1)].apd(st[id].lz);
		st[(id << 1) + 1].apd(st[id].lz);
		st[id].lz=0;
	}
	void upd(int l, int r, int id, int u, int v, int val){
		if (r < u || v < l) return;
		if (u <= l && r <= v) {
			st[id].apd(val);
			return;
		}
		down(id);
		int mid = (l+r)>>1;
		upd(l, mid, (id << 1), u, v, val);
		upd(mid+1, r, (id << 1) + 1, u, v, val);
		
		st[id].Max = max(st[(id<<1)].Max, st[(id<<1)+1].Max);
	}
	ll get(int l, int r, int id, int u, int v){
		if (r < u || v < l) return -1e18;
		if (u <= l && r <= v) return st[id].Max;
		down(id);
		int mid=(l+r)>>1;
		return max(get(l, mid, (id << 1), u, v), get(mid+1, r, (id << 1) + 1, u, v));
	}
} s3x;
void solve(){
	cin >> n;
	
	vector <int> tmp;
	for (int i = 1; i <= n; i ++ ){
		cin >> Q[i].l >> Q[i].r >> Q[i].w;
		tmp.push_back(Q[i].l);
		tmp.push_back(Q[i].l+1);
		tmp.push_back(Q[i].r);
	}
	; 
	
	sort(tmp.begin(), tmp.end()); 
	sort(Q+1, Q+n+1, cmp);
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end()); int N = tmp.size();
	ll ans = 0;
	for (int i = 1; i <= n; i ++ ){
		int kL = lower_bound(tmp.begin(), tmp.end(), Q[i].l) - tmp.begin() + 1;
		s3x.upd(1, N, 1, 1, kL, Q[i].w);
		
		if (i == n || Q[i].r != Q[i+1].r){
			
			int kR = lower_bound(tmp.begin(), tmp.end(), Q[i].r) - tmp.begin() + 1;
			ans = max(ans, s3x.get(1, N, 1, 1, Q[i].r));
//			if (Q[i].r == 89){
////				cout << s3x.get(1, N, 1, 1, 40) <<endl;
//			}
		}	
	}
	cout << ans <<endl;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	freopen("SSEQ.INP", "r", stdin);
	freopen("SSEQ.OUT", "w", stdout);
	solve();
	
}



