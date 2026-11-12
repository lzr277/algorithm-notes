#include <bits/stdc++.h>
#define int long long
using namespace std;

// 教学接口：4行，每行4个整数，0为空；输出首个解或No solution。
int g[4][4];
bool row[4][5],col[4][5],box[4][5];
bool dfs(int u)
{
    if(u==16) return true;
    int x=u/4,y=u%4,b=x/2*2+y/2;
    if(g[x][y]) return dfs(u+1);
    for(int v=1;v<=4;v++)
    {
        if(row[x][v]||col[y][v]||box[b][v]) continue;
        g[x][y]=v;
        row[x][v]=col[y][v]=box[b][v]=true;
        if(dfs(u+1)) return true;
        row[x][v]=col[y][v]=box[b][v]=false;
        g[x][y]=0;
    }
    return false;
}
signed main()
{
    bool valid=true;
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            int v;
            cin>>v;
            g[x][y]=v;
            if(v<0||v>4) valid=false;
            if(v<1||v>4) continue;
            int b=x/2*2+y/2;
            if(row[x][v]||col[y][v]||box[b][v]) valid=false;
            row[x][v]=col[y][v]=box[b][v]=true;
        }
    }
    if(!valid||!dfs(0)) cout<<"No solution\n";
    else
    {
        for(int x=0;x<4;x++)
            for(int y=0;y<4;y++) cout<<g[x][y]<<(y==3?'\n':' ');
    }
    return 0;
}
