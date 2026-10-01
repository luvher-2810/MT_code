struct NTT{
	const int mod=998244353;
	const int g=3;

	int pw(int a,int b){
		int r=1;
		while(b){
			if(b&1) r=r*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return r;
	}

	void ntt(vector<int> &a,bool inv){
		int n=a.size();

		for(int i=1,j=0;i<n;i++){
			int bit=n>>1;
			for(;j&bit;bit>>=1) j^=bit;
			j^=bit;
			if(i<j) swap(a[i],a[j]);
		}

		for(int len=2;len<=n;len<<=1){
			int wlen=pw(g,(mod-1)/len);
			if(inv) wlen=pw(wlen,mod-2);

			for(int i=0;i<n;i+=len){
				int w=1;
				for(int j=0;j<len/2;j++){
					int u=a[i+j];
					int v=a[i+j+len/2]*w%mod;

					a[i+j]=u+v;
					if(a[i+j]>=mod) a[i+j]-=mod;

					a[i+j+len/2]=u-v;
					if(a[i+j+len/2]<0) a[i+j+len/2]+=mod;

					w=w*wlen%mod;
				}
			}
		}

		if(inv){
			int iv=pw(n,mod-2);
			for(int i=0;i<n;i++) a[i]=a[i]*iv%mod;
		}
	}

	vector<int> mul(vector<int> a,vector<int> b){
		int sz=a.size()+b.size()-1;
		int n=1;
		while(n<sz) n<<=1;

		a.resize(n);
		b.resize(n);

		ntt(a,0);
		ntt(b,0);

		for(int i=0;i<n;i++) a[i]=a[i]*b[i]%mod;

		ntt(a,1);
		a.resize(sz);
		return a;
	}
};