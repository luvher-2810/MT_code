#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define task ""
const int MOD = 1e9+7;
const int maxn = 1e6+2;
const ll INF = 1e18;
struct NodeMx{
	int val, id, xx;
	bool operator<(const NodeMx &other) const {
		return val < other.val;
	}
};
struct NodeMn{
	int val, id, xx;
	bool operator<(const NodeMn &other) const {
		return val > other.val;
	}
};
int n,m;
int a[maxn], x[maxn], pos[maxn];
priority_queue<NodeMx> Mx, q;
priority_queue<NodeMn> Mn;
int mx=-INF;
//multiset<int> s;
int getMx(int ID){
	int res = -1;
	NodeMx x1={-1,-1,-1};
	while(!Mx.empty()){
		NodeMx top=Mx.top();//Mx.pop();
		if(top.xx!=pos[top.id]){
			Mx.pop();
			continue;
		}		
		if(top.id==ID){
			x1=top;
			Mx.pop();
			continue;
		}
		res=top.val;
		break;
	}
	if(x1.id!=-1) Mx.push(x1);
	return res;
}
int getMn(int ID){
	int res = INF;
	NodeMn x1={-1,-1,-1};
	while(!Mn.empty()){
		NodeMn top=Mn.top();//Mn.pop();
		if(top.xx!=pos[top.id]){
			Mn.pop();
			continue;
		}		
		if(top.id==ID){
			x1=top;
			Mn.pop();
			continue;
		}
		res=top.val;
		break;
	}
	if(x1.id!=-1) Mn.push(x1);
	return res;
}
namespace sub12{
	void solve(){
		vector<int> ans(m+3, INF);
		for(int k=1;k<=mx;k++) for(int j=k;j<=mx;j++){
			bitset<3005> f;
			f[0]=1;
			bool ok=true;
			for(int i=1;i<=n;i++){
				bitset<3005> xf;
				bool check=false;
				for(int t=1;t<=a[i];t++){
					int v1=a[i]/t, v2=v1+(a[i]%t!=0);
					if(v1>=k && v2<=j){
						xf |= (f<<t);
						check=true;
					}
				}
				if(!check){
					ok=false;
					break;
				}
				f=xf;
			}
			if(ok){
				for(int i=1;i<=m;i++){
					if(n+i<=3000 && f[n+i]) ans[i]=min(ans[i],j-k);
				}
			}
		}
		for(int i=1;i<=m;i++) cout << ans[i]<<" ";
	}
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(task".inp","r",stdin);
//	freopen(task".out","w",stdout);
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		x[i]=1;pos[i]=0;
		q.push({a[i]/2,i,0});
		Mx.push({a[i], i,0});
		Mn.push({a[i],i,0});
//		s.insert(a[i]);
		mx=max(mx, a[i]);
	}
	if(n<=1000 && m<=2000 && mx<=10){
		sub12::solve();
		return 0; 
	}
	for(int i=1;i<=m;i++){
//		while(!Mx.empty() && Mx.top().xx!=pos[Mx.top().id]) Mx.pop();
//		int I=Mx.top().id;
//		while(!q.empty() && q.top().xx!=pos[q.top().id]) q.pop();
//		int J=q.top().id;
		int I=-1; vector<NodeMx> tmpI;
		while(!Mx.empty()){
			NodeMx top=Mx.top();Mx.pop();
			if(top.xx!=pos[top.id]) continue;
			if(x[top.id]==a[top.id]){
				tmpI.push_back(top);
				continue;
			}
			I=top.id;
			tmpI.push_back(top);
			break;
		}
		for(auto it : tmpI) Mx.push(it);
		
		int J=-1; vector<NodeMx> tmpJ;
		while(!q.empty()){
			NodeMx top=q.top();q.pop();
			if(top.xx!=pos[top.id]) continue;
			if(x[top.id]==a[top.id]){
				tmpJ.push_back(top);
				continue;
			}
			J=top.id;
			tmpJ.push_back(top);
			break;
		}
		for(auto it : tmpJ) q.push(it);
		int res=I, ans=INF, fmx=-1, fmn=-1;
		for(int i=0;i<2;i++){
			int C=(i==0 ? I : J);
			if(C==-1) continue;
			int MX=getMx(C), newMx=max(MX, (a[C]+x[C])/(x[C]+1));
			int MN=getMn(C), newMn=min(MN, a[C]/(x[C]+1));
			int dif=newMx-newMn;
			if(dif<ans || (dif==ans && newMx<fmx)){
				ans=dif;
				fmn=newMn;
				fmx=newMx;
				res=C;
			}
		}
		if(res==-1){
			cout << ans <<" ";
			continue;
		}
		x[res]++;pos[res]++;
		Mx.push({(a[res]+x[res]-1)/x[res], res, pos[res]});
		Mn.push({(a[res])/(x[res]), res, pos[res]});
		if(x[res]<a[res]) q.push({(a[res]/(x[res]+1)), res, pos[res]});
		cout << ans <<" ";
	}
	return 0;
}
//luv


