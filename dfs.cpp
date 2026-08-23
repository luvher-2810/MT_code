#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int n, m;
int a[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void dfs(int x, int y) {
    visited[x][y] = true;
    for(int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx >=1 && nx <= n && ny >=1 && ny <= m &&
           !visited[nx][ny] && a[nx][ny] == 1) {
            dfs(nx, ny);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin >> a[i][j];

    memset(visited, false, sizeof(visited));

    int ans = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]==1 && !visited[i][j]){
                ans++;
                dfs(i,j);
            }

    cout << ans;
    return 0;
}

