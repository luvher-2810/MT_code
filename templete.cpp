#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define fi first
#define se second
#define pb push_back
#define ii pair<int,int>
#define vt vector<int>
#define int long long
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define REP(i,n) for(int i=0;i<(n);i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)

#define ALL(v) (v).begin(),(v).end()
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1LL)
#define el "\n"

template<class T>
bool maximize(T &a,const T &b){
    if(a<b){
        a=b;
        return true;
    }
    return false;
}

template<class T>
bool minimize(T &a,const T &b){
    if(a>b){
        a=b;
        return true;
    }
    return false;
}

const int MOD=998244353;
const int mod=998244353;
const int N=1e6+5;
const ll INF=1e18;

int par[N],sz[N], up[20][N], depth[N];
int lg[N];
int f0[N], f1[N], xx[N];
int ID[N], IX[N];
int find(int x){
	if(x==par[x]) return x;
	return par[x]=find(par[x]);
} 
void unite(int a, int b){
	a=find(a);b=find(b);
	if(a==b) return;
	if(sz[a]<sz[b]) swap(a,b);
	par[b]=a;
	sz[a]+=sz[b];
}
int lca(int a, int b){
	if(!a || !b) return a|b;
	if(depth[a]<depth[b]) swap(a,b);
	int dep=depth[a]-depth[b];
	FOR(i,0,19) if(BIT(dep,i)) a=up[i][a];
	if(a==b) return a;
	FOR(i,19,0) if(up[i][a] != up[i][b]){
		a=up[i][a];
		b=up[i][b];
	} 
	return up[0][a];
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(0);
	lg[0]=1;
	FOR(i,1,1e6) lg[i]=(lg[i-1]*2)%MOD;
	int t; cin>>t;
    while(t--){
    	int n,m; cin >> n >> m;
    	string a[n+2];
    	FOR(i,1,n){
    		cin >> a[i];
    		a[i]=" "+a[i];
		}
		FOR(i,0,n*m){
		    f0[i]=f1[i]=xx[i]=0;
		    ID[i]=IX[i]=0;
		    depth[i]=0;
		    par[i]=i;
		    sz[i]=1;
		    FOR(k,0,19) up[k][i]=0;
		}
		FOR(i,1,n) FOR(j,1,m){
			int pos=(i-1)*m+j;
			if(a[i][j]=='0') continue;
			if(i==1 && j==1) f1[pos]=1;
			else{
				if(i>1 && f1[pos-m]) f1[pos]=1;
				if(j>1 && f1[pos-1]) f1[pos]=1;
			}
		}
		FORD(i,n,1) FORD(j,m,1){
			int pos=(i-1)*m+j;
			if(a[i][j]=='0') continue;
			if(i==n && j==m) f0[pos]=1;
			else{
				if(i<n && f0[pos+m]) f0[pos]=1;
				if(j<m && f0[pos+1]) f0[pos]=1;
			}
		}
		FOR(i,1,n*m) xx[i]=f1[i]&f0[i];
		int ss=accumulate(xx+1,xx+m*n+1,0ll);
		if(ss==0){
			cout <<(lg[n*m]-1+MOD)%MOD <<el;
			continue;
		}
		//FOR(i,0,19) up[i][0]=up[i][1]=up[i][n*m]=0;
		depth[0]=0;
		depth[1]=1;
		ID[1]=0;
		FOR(i,1,n) FOR(j,1,m){
			int pos=(i-1)*m+j;
			if(!xx[pos] || pos==1) continue;
			int x1=0,x2=0;
			if(i>1 && xx[pos-m]) x1=pos-m;
			if(j>1 && xx[pos-1]){
				if(!x1) x1=pos-1;
				else x2=pos-1;
			}
			int x=(x2 ? lca(x1,x2) : x1);
			ID[pos]=x;
			depth[pos]=depth[x]+1;
			up[0][pos]=x;
			FOR(k,1,19) up[k][pos]=up[k-1][up[k-1][pos]];
		}
		depth[n*m]=1;
		IX[n*m]=0;
		FORD(i,n,1) FORD(j,m,1){
			int pos=(i-1)*m+j;
			if(!xx[pos] || pos==n*m) continue;
			int x1=0,x2=0;
			if(i<n && xx[pos+m]) x1=pos+m;
			if(j<m && xx[pos+1]){
				if(!x1) x1=pos+1;
				else x2=pos+1;
			}
			int x=(x2 ? lca(x1,x2) : x1);
			IX[pos]=x;
			depth[pos]=depth[x]+1;
			up[0][pos]=x;
			FOR(k,1,19) up[k][pos]=up[k-1][up[k-1][pos]];
		}
		FOR(i,1,n*m+1) par[i]=i, sz[i]=1;
		FOR(i,1,n*m){
			if(!xx[i]) continue;
			if(ID[i] && IX[ID[i]]==i) unite(i,ID[i]);
		}
		int ans=lg[n*m-ss]-1;
		if(ans<0) ans+=MOD;
		FOR(i,1,n*m){
			if(!xx[i]) continue;
			if(find(i)==i){
				ans+=lg[sz[i]]-1;
				if(ans>=MOD) ans-=MOD;
			}
		}
		cout << ans%MOD <<el;
	}

}
