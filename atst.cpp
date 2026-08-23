#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Kích thu?c Block = 320 x?p x? can b?c hai c?a 10^5
const int S = 320;
const int MAX_B = 100005 / S + 5;

struct Block {
    int size;
    int cnt;
    long long vals[S];
    bool act[S];
    long long active_vals[S];
    long long sum[S];
} blocks[MAX_B];

pair<long long, int> sorted_a[100005];
int pos_of_step[100005];

int main() {
    // T?i uu I/O cho C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    for (int i = 1; i <= n; i++) {
        cin >> sorted_a[i - 1].first;
        sorted_a[i - 1].second = i;
    }
    
    // Sort toàn b? các ph?n t? du?c chèn offline
    sort(sorted_a, sorted_a + n);
    
    int num_blocks = (n + S - 1) / S;
    for (int i = 0; i < num_blocks; i++) {
        blocks[i].size = 0;
        blocks[i].cnt = 0;
        for (int j = 0; j < S; j++) {
            blocks[i].act[j] = false;
        }
    }
    
    // Kh?i t?o các ph?n t? vào dúng Block v?t lý c?a nó
    for (int i = 0; i < n; i++) {
        int b = i / S;
        int idx = i % S;
        blocks[b].vals[idx] = sorted_a[i].first;
        blocks[b].size++;
        pos_of_step[sorted_a[i].second] = i;
    }
    
    for (int step = 1; step <= n; step++) {
        int pos = pos_of_step[step];
        int b = pos / S;
        int idx = pos % S;
        
        // Kích ho?t ph?n t? trong m?ng
        blocks[b].act[idx] = true;
        
        // Rebuild l?i danh sách active trong O(S)
        blocks[b].cnt = 0;
        for (int i = 0; i < blocks[b].size; i++) {
            if (blocks[b].act[i]) {
                blocks[b].active_vals[blocks[b].cnt++] = blocks[b].vals[i];
            }
        }
        
        // Ch? luu b?ng tra modulo n?u k <= S d? tránh chi phí reset O(k)
        if (k <= S) {
            for (int i = 0; i < k; i++) blocks[b].sum[i] = 0;
            for (int i = 0; i < blocks[b].cnt; i++) {
                blocks[b].sum[i % k] += blocks[b].active_vals[i];
            }
        }
        
        long long ans = 0;
        long long cur_len = 0;
        
        // Truy v?n tách nhánh d?a vào d? l?n c?a K
        if (k <= S) {
            for (int j = 0; j < num_blocks; j++) {
                int c = blocks[j].cnt;
                if (c == 0) continue;
                
                int req_r = (k - (cur_len % k)) % k;
                ans += blocks[j].sum[req_r];
                cur_len += c;
            }
        } else {
            for (int j = 0; j < num_blocks; j++) {
                int c = blocks[j].cnt;
                if (c == 0) continue;
                
                int req_r = (k - (cur_len % k)) % k;
                // Khi K > S thì trong m?t block ch? t?n t?i T?I ÐA 1 ph?n t? nh?y trúng
                if (req_r < c) {
                    ans += blocks[j].active_vals[req_r];
                }
                cur_len += c;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
