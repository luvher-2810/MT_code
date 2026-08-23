#include <bits/stdc++.h>
using namespace std;

// basic debugging macros
int __i__,__j__;
#define printLine(l) for(__i__=0;__i__<l;__i__++){cout<<"-";}cout<<endl
#define printLine2(l,c) for(__i__=0;__i__<l;__i__++){cout<<c;}cout<<endl
#define printVar(n) cout<<#n<<": "<<n<<endl
#define printArr(a,l) cout<<#a<<": ";for(__i__=0;__i__<l;__i__++){cout<<a[__i__]<<" ";}cout<<endl
#define print2dArr(a,r,c) cout<<#a<<":\n";for(__i__=0;__i__<r;__i__++){for(__j__=0;__j__<c;__j__++){cout<<a[__i__][__j__]<<" ";}cout<<endl;}
#define print2dArr2(a,r,c,l) cout<<#a<<":\n";for(__i__=0;__i__<r;__i__++){for(__j__=0;__j__<c;__j__++){cout<<setw(l)<<setfill(' ')<<a[__i__][__j__]<<" ";}cout<<endl;}

// advanced debugging class
// debug 1,2,'A',"test";
class _Debug {
    public:
        template<typename T>
        _Debug& operator,(T val) {
            cout << val << endl;
            return *this;
        }
};
#define debug _Debug(),

// define
#define MAX_VAL 999999999
#define MAX_VAL_2 999999999999999999LL
#define EPS 1e-6

// typedef
typedef unsigned int UI;
typedef long long int LLI;
typedef unsigned long long int ULLI;
typedef unsigned short int US;
typedef pair<int,int> pii;
typedef pair<LLI,LLI> plli;
typedef vector<int> vi;
typedef vector<LLI> vlli;
typedef vector<pii> vpii;
typedef vector<plli> vplli;

// ---------- END OF TEMPLATE ----------

int B[30000],P[30000];
vi doge[30000];
int dist[30000],dist2[30000];
priority_queue<pii> H;
bool comp(int a,int b) {
    if ((a < 2) || (b < 2)) return a < b;
    else return P[a] < P[b];
}
bool comp2(int a,int b) {
    if ((a < 2) || (b < 2)) return a == b;
    else return P[a] == P[b];
}
int main() {
    int i;
    int N,M;
    scanf("%d %d",&N,&M);
    for (i = 0; i < M; i++) {
        scanf("%d %d",&B[i],&P[i]);
        doge[B[i]].push_back(i);
    }

    P[1] = -1;
    for (i = 0; i < N; i++) {
        sort(doge[i].begin(),doge[i].end(),comp);
        doge[i].resize(unique(doge[i].begin(),doge[i].end(),comp2)-doge[i].begin());
    }

    int j,u,d,w;
    fill(dist,dist+M,-1);
    fill(dist2,dist2+N,MAX_VAL);
    for (i = 0; i < doge[B[0]].size(); i++) {
        u = doge[B[0]][i];
        dist[u] = 0,dist2[B[u]] = 0;
        H.push(make_pair(0,u));
    }
    while (!H.empty()) {
        u = H.top().second;
        d = -H.top().first;
        H.pop();

        if (d > dist[u]) continue;
        else if (u == 1) break;
        for (i = B[u]+P[u],w = 1; i < N; i += P[u],w++) {
            if ((dist2[B[u]]+w) < dist2[i]) {
                for (j = 0; j < doge[i].size(); j++) {
                    int v = doge[i][j];
                    if ((P[u] != P[v]) && ((dist[v] == -1) || ((dist[u]+w) < dist[v]))) {
                        dist[v] = dist[u]+w;
                        H.push(make_pair(-dist[v],v));
                    }
                }
                dist2[i] = dist2[B[u]]+w;
            }
        }
        for (i = B[u]-P[u],w = 1; i >= 0; i -= P[u],w++) {
            if ((dist2[B[u]]+w) < dist2[i]) {
                for (j = 0; j < doge[i].size(); j++) {
                    int v = doge[i][j];
                    if ((P[u] != P[v]) && ((dist[v] == -1) || ((dist[u]+w) < dist[v]))) {
                        dist[v] = dist[u]+w;
                        H.push(make_pair(-dist[v],v));
                    }
                }
                dist2[i] = dist2[B[u]]+w;
            }
        }
    }
    printf("%d\n",dist[1]);

    return 0;
}

