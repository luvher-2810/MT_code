#include <iostream>
#include <vector>
#include <numeric>
#include <cctype>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> tree;
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
    
    // Finds the k-th available element (1-indexed)
    int find_kth(int k) {
        int pos = 0;
        for (int i = 20; i >= 0; i--) { // 2^20 > 2*10^5
            if (pos + (1 << i) <= n && tree[pos + (1 << i)] < k) {
                pos += (1 << i);
                k -= tree[pos];
            }
        }
        return pos + 1;
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<char> type(n + 1);
    vector<long long> val(n + 1);
    vector<int> p(n + 1, 0);
    vector<bool> used(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        c = tolower(c);
        type[i] = c;
        cin >> val[i];
        if (type[i] == 'p') {
            p[i] = val[i];
            used[p[i]] = true;
        }
    }
    
    FenwickTree avail(n);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            avail.add(i, 1);
        }
    }
    
    FenwickTree placed(n);
    long long current_inversions = 0;
    
    for (int i = 1; i <= n; i++) {
        if (type[i] == 'p') {
            int c_i = (i - 1) - placed.query(p[i]);
            current_inversions += c_i;
            placed.add(p[i], 1);
        } else {
            long long target_inversions = val[i];
            long long c_i = target_inversions - current_inversions;
            
            // We need c_i elements in the prefix to be strictly greater than p[i]
            // This means we need exactly (i - 1 - c_i) elements in the prefix to be <= p[i]
            int required_smaller = (i - 1) - c_i;
            
            // To satisfy this, we query our available unused elements.
            // Since the exact value is governed by the unused pool to match future constraints properly,
            // we isolate the correct unused element based on how many elements are currently active.
            int left = 1, right = n, best = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (placed.query(mid) <= required_smaller) {
                    best = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            // Find the maximum available valid element bounded by our binary search range
            int k = avail.query(best);
            int chosen = avail.find_kth(k);
            
            p[i] = chosen;
            avail.add(chosen, -1);
            placed.add(chosen, 1);
            current_inversions = target_inversions;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        cout << p[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
