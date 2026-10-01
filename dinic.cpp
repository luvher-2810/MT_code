struct Dinic{
	struct Edge{
		int v;
		long long cap;
		int rev;
	};
	int n;
	vector<vector<Edge> > g;
	vector<int> lev, it;

	Dinic(int n){
		this->n=n;
		g.resize(n+1);
		lev.resize(n+1);
		it.resize(n+1);
	}

	void addEdge(int u,int v,long long cap){
		Edge a={v,cap,(int)g[v].size()};
		Edge b={u,0,(int)g[u].size()};
		g[u].push_back(a);
		g[v].push_back(b);
	}

	bool bfs(int s,int t){
		for(int i=1;i<=n;i++) lev[i]=-1;
		queue<int> q;
		lev[s]=0;
		q.push(s);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<(int)g[u].size();i++){
				Edge &e=g[u][i];
				if(e.cap>0 && lev[e.v]==-1){
					lev[e.v]=lev[u]+1;
					q.push(e.v);
				}
			}
		}
		return lev[t]!=-1;
	}

	long long dfs(int u,int t,long long f){
		if(u==t) return f;
		for(int &i=it[u];i<(int)g[u].size();i++){
			Edge &e=g[u][i];
			if(e.cap>0 && lev[e.v]==lev[u]+1){
				long long ret=dfs(e.v,t,min(f,e.cap));
				if(ret>0){
					e.cap-=ret;
					g[e.v][e.rev].cap+=ret;
					return ret;
				}
			}
		}
		return 0;
	}

	long long maxFlow(int s,int t){
		long long ans=0;
		const long long inf=4e18;
		while(bfs(s,t)){
			for(int i=1;i<=n;i++) it[i]=0;
			while(true){
				long long f=dfs(s,t,inf);
				if(f==0) break;
				ans+=f;
			}
		}
		return ans;
	}
};