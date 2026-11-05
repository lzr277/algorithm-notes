#include <iostream>
using namespace std;
long long dp[21][21]{};
bool blocked[21][21]{};
int main() {
    int n,m,hx,hy; cin >> n >> m >> hx >> hy;
    int dx[]={0,1,1,-1,-1,2,2,-2,-2};
    int dy[]={0,2,-2,2,-2,1,-1,1,-1};
    for(int k=0;k<9;++k) {
        int x=hx+dx[k], y=hy+dy[k];
        if(x>=0 && x<=n && y>=0 && y<=m) blocked[x][y]=true;
    }
    for(int x=0;x<=n;++x) for(int y=0;y<=m;++y) {
        if(blocked[x][y]) continue;
        if(x==0 && y==0) { dp[x][y]=1; continue; }
        if(x>0) dp[x][y]+=dp[x-1][y];
        if(y>0) dp[x][y]+=dp[x][y-1];
    }
    cout << dp[n][m] << '\n';
}
