// 输入 n、m 和 m 条有向边；求1到n最少边数，不可达输出-1。
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;if(!(cin>>n>>m)||n<1||m<0)return 1;
    vector<vector<int>>g(n+1);
    for(int i=0,a,b;i<m;++i){cin>>a>>b;if(a<1||a>n||b<1||b>n)return 1;g[a].push_back(b);}
    vector<int>dist(n+1,-1);queue<int>q;dist[1]=0;q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u])if(dist[v]==-1){dist[v]=dist[u]+1;q.push(v);}
    }
    cout<<dist[n]<<'\n';
}
