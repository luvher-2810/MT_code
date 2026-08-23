#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define ii pair<int,int>
#define li pair<ll , int>
#define fi first
#define se second
#define lwb lower_bound
#define upb upper_bound
#define pb push_back
#define N 1000005
#define MOD 1000000007

void read(){
	 freopen("txt.INP", "r", stdin);
    freopen("txt.OUT", "w", stdout);
}


/*----------------------------------*END*----------------------------------*/

int snt[N];

void sang(){
	
	for(int i = 2; i * i <= N; i++){
		if(snt[i] == 0){
			for(int j = i; j <= N; j += i){
				if(snt[j] == 0)
				snt[j] = i;
			}
		}
	}
	for(int i=1;i<=N;i++) if(!snt[i]) snt[i]=i;
}

map<int,int> cnt;

int n , t;




int main(){
	//read();
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> t;
	sang();
//	
	while(t--){
		
		cin >> n;
		
		for(int i = 1 ; i<= n;){
			int h = (n / i), r=n/h;
			while(h>1){
				int p=snt[h];
				ll e=0;
				while(h%p==0){
					h/=p;
					e++;
				}
				cnt[p]+=e*(r-i+1);
			}
			i=r+1;
		}
		ll kq = 1;
		
		for(pair<int,int> i : cnt){
//				cout << i <<' ' << cnt[i] << '\n';
				kq =( kq * (i.second + 1) ) % 998244353;
		}
		cout << kq << '\n';
		
		
		
	}
	
	
	
	
}
//MEAT!

