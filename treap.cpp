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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, b) for (int i = 0, _b = (b); i < _b; i++)
#define sum(a) accumulate(a+1,a+n+1,0ll)
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & (1LL))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define TASK "GROWING"
#define vt vector<int>
#define el "\n"
#define miti unordered_map<ll,ll>
#define ctz(x) __builtin_ctz(x)
#define popp(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
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
const int N = 2e5+10;
const ll INF = 1e18;
//--------------------------------------------------
const int MX = 600000;

struct Node{
    ll k,c,s,m,lz;
    uint32_t p;
    Node *l,*r;
} tr[MX];

int pc;
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

Node* nw(ll k,ll c){
    Node* t=&tr[++pc];
    t->k=k; t->c=c; t->s=c; t->m=k; t->lz=0;
    t->p=(uint32_t)rd();
    t->l=t->r=0;
    return t;
}

ll gs(Node* t){ return t?t->s:0; }
ll gm(Node* t){ return t?t->m:-INF; }

void up(Node* t){
    if(!t) return;
    t->s=t->c+gs(t->l)+gs(t->r);
    t->m=max(t->k,max(gm(t->l),gm(t->r)));
}

void add(Node* t,ll d){
    if(!t) return;
    t->k+=d; t->m+=d; t->lz+=d;
}

void pd(Node* t){
    if(!t||!t->lz) return;
    add(t->l,t->lz);
    add(t->r,t->lz);
    t->lz=0;
}

Node* mg(Node* a,Node* b){
    if(!a) return b;
    if(!b) return a;
    if(a->p>b->p){
        pd(a);
        a->r=mg(a->r,b);
        up(a);
        return a;
    }else{
        pd(b);
        b->l=mg(a,b->l);
        up(b);
        return b;
    }
}

void spk(Node* t,ll x,Node*& a,Node*& b){
    if(!t){ a=b=0; return; }
    pd(t);
    if(t->k<x){
        spk(t->r,x,t->r,b);
        up(t); a=t;
    }else{
        spk(t->l,x,a,t->l);
        up(t); b=t;
    }
}

void spc(Node* t,ll k,Node*& a,Node*& b){
    if(!t){ a=b=0; return; }
    if(k<=0){ a=0; b=t; return; }
    pd(t);
    ll L=gs(t->l);
    if(k<L){
        spc(t->l,k,a,t->l);
        up(t); b=t;
    }else if(k>L+t->c){
        spc(t->r,k-L-t->c,t->r,b);
        up(t); a=t;
    }else if(k==L){
        a=t->l; t->l=0; up(t); b=t;
    }else if(k==L+t->c){
        b=t->r; t->r=0; up(t); a=t;
    }else{
        ll d=k-L;
        Node* x=nw(t->k,d);
        Node* y=nw(t->k,t->c-d);
        x->p=t->p; y->p=t->p;
        x->l=t->l; x->r=0;
        y->l=0; y->r=t->r;
        up(x); up(y);
        a=x; b=y;
    }
}

Node* mg2(Node* a,Node* b){
    if(!a) return b;
    if(!b) return a;
    a->c+=b->c;
    up(a);
    return a;
}
int n,m;
//--------------------------------------------------
int32_t main(){
	faster;
	freopen(TASK".inp","r",stdin);
	freopen(TASK".out","w",stdout);
	cin>>n>>m;

    map<ll,ll> mp;
    FOR(i,1,n){
        ll x; cin>>x;
        mp[x]++;
    }

    Node* rt=0;
    for(auto it:mp) rt=mg(rt,nw(it.fi,it.se));

    FOR(i,1,m){
        char t; cin>>t;
        if(t=='C'){
            ll l,r; cin>>l>>r;
            Node *a,*b,*c;
            spk(rt,l,a,b);
            spk(b,r+1,b,c);
            cout<<gs(b)<<el;
            rt=mg(a,mg(b,c));
        }else{
            ll c,h; cin>>c>>h;
            Node *L,*R;
            spk(rt,h,L,R);

            if(gs(R)<=c){
                add(R,1);
                rt=mg(L,R);
                continue;
            }

            Node *P,*S;
            spc(R,c,P,S);

            ll r=P->m;

            Node *P1,*P2;
            spk(P,r,P1,P2);

            Node *S1,*S2;
            spk(S,r+1,S1,S2);

            add(P1,1);
            add(P2,1);

            Node *A,*B;
            spk(P1,r,A,B);

            Node *C,*D;
            spk(S2,r+2,C,D);

            Node* b1=mg2(B,S1);
            Node* b2=mg2(P2,C);

            rt=mg(L,A);
            rt=mg(rt,b1);
            rt=mg(rt,b2);
            rt=mg(rt,D);
        }
    }
}
//100077958169269
//iloveMT



