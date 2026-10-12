// 补充程序：n、容量V，随后每个物品的正体积与价值；求容量内最大价值，可不选。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,V;if(!(cin>>n>>V)||n<0||V<0)return 1;
    vector<long long>f(V+1,0);
    while(n--){int v;long long w;cin>>v>>w;if(v<=0)return 1;
        for(int j=V;j>=v;--j)f[j]=max(f[j],f[j-v]+w);
    }
    cout<<f[V]<<'\n';
}
