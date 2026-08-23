// camp.cpp
#include <bits/stdc++.h>
using namespace std;
struct DSU {
    int n; vector<int> p, r;
    DSU(int n=0): n(n), p(n+1), r(n+1,0) { for(int i=0;i<=n;i++) p[i]=i; }
    int find(int a){ return p[a]==a?a:p[a]=find(p[a]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
};

struct Edge { int u,v; double w; };
double dist(pair<double,double> a, pair<double,double> b){
    double dx=a.first-b.first, dy=a.second-b.second;
    return sqrt(dx*dx+dy*dy);
}

struct MSTResult {
    double total;
    vector<pair<int,int>> edges;
};

MSTResult compute_mst(const vector<pair<double,double>> &pts){
    int n = (int)pts.size()-1; // pts indexed from 1..n
    vector<Edge> edges; edges.reserve(n*(n-1)/2);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            edges.push_back({i,j, dist(pts[i], pts[j])});
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){ return a.w < b.w; });
    DSU dsu(n);
    MSTResult res; res.total = 0.0;
    for(auto &e: edges){
        if((int)res.edges.size() == n-1) break;
        if(dsu.unite(e.u, e.v)){
            res.edges.emplace_back(e.u, e.v);
            res.total += e.w;
        }
    }
    return res;
}

// random point uniform in circle radius R
pair<double,double> rand_in_circle(double R, mt19937 &rng){
    uniform_real_distribution<double> u(0.0,1.0), a(0.0, 2*M_PI);
    double r = sqrt(u(rng)) * R;
    double ang = a(rng);
    return { r * cos(ang), r * sin(ang) };
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double PI = 3.14159265358979323846;
    const double R = 100.0;

    int K;
    if(!(cin>>K)) return 0;
    vector<double> alpha(K+1);
    for(int i=1;i<=K;i++) cin>>alpha[i];
    double A; cin>>A;

    // terminals coords index 1..K
    vector<pair<double,double>> terminals(K+1);
    for(int i=1;i<=K;i++){
        double ang = alpha[i] * PI / 180.0;
        terminals[i] = { R * cos(ang), R * sin(ang) };
    }

    // baseline: MST on terminals only
    vector<pair<double,double>> pts_base(K+1);
    for(int i=1;i<=K;i++) pts_base[i] = terminals[i];
    MSTResult base = compute_mst(pts_base);

    // also consider star at center (one Steiner point)
    vector<pair<double,double>> center_all(K+2);
    for(int i=1;i<=K;i++) center_all[i] = terminals[i];
    center_all[K+1] = {0.0, 0.0};
    MSTResult star = compute_mst(center_all);

    // best solution (store Steiner points coordinates separately)
    double best_total;
    vector<pair<double,double>> best_steiner; // coordinates of steiner points (order matters for output)
    vector<pair<int,int>> best_edges; // edges in MST over (terminals + steiner)

    // initialize best with better of baseline and star
    if(base.total <= star.total){
        best_total = base.total;
        best_steiner.clear();
        best_edges = base.edges;
    } else {
        best_total = star.total;
        best_steiner.clear();
        best_steiner.push_back(center_all[K+1]);
        best_edges = star.edges;
    }

    // initial Steiner set: add midpoint of longest edges of base MST (up to 3)
    // compute edge midpoints
    vector<pair<int,int>> long_edges = base.edges;
    // compute lengths
    vector<pair<double,int>> lens;
    for(size_t i=0;i<long_edges.size();i++){
        int u=long_edges[i].first, v=long_edges[i].second;
        double L = dist(terminals[u], terminals[v]);
        lens.push_back({L, (int)i});
    }
    sort(lens.rbegin(), lens.rend());
    vector<pair<double,double>> initS;
    for(size_t t=0; t<lens.size() && initS.size()<3; ++t){
        int idx = lens[t].second;
        int u = long_edges[idx].first, v = long_edges[idx].second;
        auto mid = make_pair((terminals[u].first+terminals[v].first)/2.0, (terminals[u].second+terminals[v].second)/2.0);
        initS.push_back(mid);
    }
    // try initial candidate (initS) as starting point
    if(!initS.empty()){
        int M = (int)initS.size();
        vector<pair<double,double>> all(K+M+1);
        for(int i=1;i<=K;i++) all[i]=terminals[i];
        for(int i=0;i<M;i++) all[K+1+i]=initS[i];
        MSTResult r = compute_mst(all);
        if(r.total < best_total){
            best_total = r.total;
            best_steiner = initS;
            best_edges = r.edges;
        }
    }

    // setup RNG
    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> uni01(0.0,1.0);
    // simulated annealing parameters
    int MAX_ITERS = 4000; // total iterations of SA (tuneable)
    double T = 5.0;
    double T_end = 1e-3;
    double cooling = pow(T_end / T, 1.0 / max(1, MAX_ITERS-1));

    // current solution represented by vector steiner (coords)
    vector<pair<double,double>> curS = best_steiner;
    double cur_total;
    {
        int M = (int)curS.size();
        vector<pair<double,double>> all(K+M+1);
        for(int i=1;i<=K;i++) all[i]=terminals[i];
        for(int i=0;i<M;i++) all[K+1+i]=curS[i];
        MSTResult r = compute_mst(all);
        cur_total = r.total;
    }

    // SA loop
    for(int iter=0; iter<MAX_ITERS; ++iter){
        // choose operation
        double p = uni01(rng);
        vector<pair<double,double>> candS = curS;
        if(p < 0.30 && (int)candS.size() < 25){
            // add a random point
            candS.push_back(rand_in_circle(R, rng));
        } else if(p < 0.40 && (int)candS.size() > 0){
            // remove a random existing point
            int idx = rng() % (int)candS.size();
            candS.erase(candS.begin() + idx);
        } else if((int)candS.size() > 0){
            // move one existing point (jitter)
            int idx = rng() % (int)candS.size();
            double big_jump = (uni01(rng) < 0.12) ? 1.0 : 0.0; // occasional big jump
            pair<double,double> p0 = candS[idx];
            double maxd = big_jump ? R : 25.0; // if big_jump allow to roam whole circle
            // jitter by random vector with decaying radius depending on temperature
            double scale = maxd * (0.6 * (T / 5.0) + 0.1);
            uniform_real_distribution<double> ang(0.0, 2*M_PI);
            double a = ang(rng);
            uniform_real_distribution<double> rr(0.0,1.0);
            double r = sqrt(rr(rng)) * scale;
            double nx = p0.first + r * cos(a);
            double ny = p0.second + r * sin(a);
            // if outside circle, project back to inside
            double d2 = nx*nx + ny*ny;
            if(d2 > R*R){
                double d = sqrt(d2);
                nx = nx / d * (R - 1e-9);
                ny = ny / d * (R - 1e-9);
            }
            candS[idx] = {nx, ny};
        } else {
            // curS empty and no add (rare), so add center
            candS.push_back({0.0, 0.0});
        }

        // evaluate candidate
        int M = (int)candS.size();
        vector<pair<double,double>> all(K+M+1);
        for(int i=1;i<=K;i++) all[i]=terminals[i];
        for(int i=0;i<M;i++) all[K+1+i]=candS[i];
        MSTResult r = compute_mst(all);
        double cand_total = r.total;

        bool accept = false;
        if(cand_total < cur_total) accept = true;
        else {
            double delta = cand_total - cur_total;
            double prob = exp(-delta / max(1e-9, T));
            if(uni01(rng) < prob) accept = true;
        }
        if(accept){
            curS.swap(candS);
            cur_total = cand_total;
            // keep best
            if(cur_total < best_total){
                best_total = cur_total;
                best_steiner = curS;
                best_edges = r.edges;
            }
        }
        // cool
        T *= cooling;
    }

    // Final: best found
    int M = (int)best_steiner.size();
    // Build final points vector (1..K terminals, K+1..K+M steiner)
    vector<pair<double,double>> all(K+M+1);
    for(int i=1;i<=K;i++) all[i]=terminals[i];
    for(int i=0;i<M;i++) all[K+1+i]=best_steiner[i];
    MSTResult final_res = compute_mst(all);
    // final_res.edges are edges between 1..K+M

    // Output: M, coords (4 decimals), then K+M-1 edges
    cout.setf(std::ios::fixed);
    cout<<setprecision(0); // print M as integer without decimals
    cout<<M<<"\n";
    if(M>0){
        cout.setf(std::ios::fixed);
        cout<<setprecision(4);
        for(int i=0;i<M;i++){
            cout<<best_steiner[i].first<<" "<<best_steiner[i].second<<"\n";
        }
    }
    // edges count should be K+M-1 (MST on K+M nodes)
    for(auto &e: final_res.edges){
        cout<<e.first<<" "<<e.second<<"\n";
    }

    // Optional: print to cerr some diagnostics
    cerr.setf(std::ios::fixed);
    cerr<<setprecision(6);
    cerr<<"best total length B = "<<final_res.total<<"\n";
    cerr<<"Alice A = "<<A<<", diff = "<<final_res.total - A<<"\n";
    cerr<<"used Steiner M = "<<M<<"\n";

    return 0;
}

