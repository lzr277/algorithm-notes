#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int x,y;
}q[160005];
int n,m,d[405][405];
int dx[8]={-2,-2,-1,-1,1,1,2,2};
int dy[8]={-1,1,-2,2,-2,2,-1,1};
signed main()
{
    int sx,sy;
    cin>>n>>m>>sx>>sy;
    memset(d,-1,sizeof d);
    int hh=0,tt=0;
    q[0]={sx,sy};
    d[sx][sy]=0;
    while(hh<=tt)
    {
        node t=q[hh++];
        for(int i=0;i<8;i++)
        {
            int x=t.x+dx[i],y=t.y+dy[i];
            if(x<1||x>n||y<1||y>m) continue;
            if(d[x][y]!=-1) continue;
            d[x][y]=d[t.x][t.y]+1;
            q[++tt]={x,y};
        }
    }
    for(int x=1;x<=n;x++)
        for(int y=1;y<=m;y++) cout<<d[x][y]<<(y==m?'\n':' ');
    return 0;
}
