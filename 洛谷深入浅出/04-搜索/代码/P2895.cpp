#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=305,INF=1000000000;
struct node
{
    int x,y;
}q[N*N];
int death[N][N],d[N][N];
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
signed main()
{
    for(int x=0;x<N;x++)
        for(int y=0;y<N;y++) death[x][y]=INF;
    int m;
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,t;
        cin>>x>>y>>t;
        for(int j=0;j<5;j++)
        {
            int a=x+dx[j],b=y+dy[j];
            if(a>=0&&a<N&&b>=0&&b<N)
                death[a][b]=min(death[a][b],t);
        }
    }
    if(death[0][0]==0)
    {
        cout<<-1<<'\n';
        return 0;
    }
    memset(d,-1,sizeof d);
    int hh=0,tt=0;
    q[0]={0,0};
    d[0][0]=0;
    while(hh<=tt)
    {
        node u=q[hh++];
        if(death[u.x][u.y]==INF)
        {
            cout<<d[u.x][u.y]<<'\n';
            return 0;
        }
        for(int i=1;i<=4;i++)
        {
            int x=u.x+dx[i],y=u.y+dy[i],time=d[u.x][u.y]+1;
            if(x<0||x>=N||y<0||y>=N) continue;
            if(d[x][y]!=-1||time>=death[x][y]) continue;
            d[x][y]=time;
            q[++tt]={x,y};
        }
    }
    cout<<-1<<'\n';
    return 0;
}
