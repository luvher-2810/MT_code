#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int SEED = 1;
    if(argc >= 2) SEED = atoi(argv[1]);
    srand(SEED);

    int n = rand()%20 + 5;  // s? hàng 5..24 (ð? d? debug)
    int m = rand()%20 + 5;  // s? c?t 5..24

    cout << n << " " << m << "\n";

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int val = rand()%2; // 0 ho?c 1
            cout << val << (j==m ? '\n' : ' ');
        }
    }

    return 0;
}

