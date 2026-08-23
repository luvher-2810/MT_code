#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define fi first
#define se second
#define ii pair<int, int>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK "chut"

const int N = 1005;

int n;
ii a[N];
map<int, int> fx, fy;
map<ii, int> cnt;

int32_t main(){
    faster;
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
	    
	cin >> n;
    
    FOR(i, 1, n){
        cin >> a[i].fi >> a[i].se;
        fx[a[i].fi]++;
        fy[a[i].se]++;
        cnt[{a[i].fi, a[i].se}]++;
    }
    
    int ans = 0;
    FOR(i, 1, n){
        int xx = 0, yy = 0;
        int count_C = cnt[{a[i].fi, a[i].se}];
        
        FOR(j, 1, n){
            // TH1
            if(a[j].se == a[i].se && a[j].fi > a[i].fi){
                ii A = {2 * a[i].fi - a[j].fi, a[i].se};
                auto it = cnt.find(A);
                if(it != cnt.end()) {
                    xx += it->second;
                }
            }
            
            // TH2
            if(a[j].fi == a[i].fi && a[j].se > a[i].se){
                ii A = {a[i].fi, 2 * a[i].se - a[j].se};
                auto it = cnt.find(A);
                if(it != cnt.end()) {
                    yy += it->second; 
                }
            }
        }
        ans += xx * (fx[a[i].fi] - count_C) + yy * (fy[a[i].se] - count_C);
    }
    
    cout << ans << "\n";
    return 0;
}
