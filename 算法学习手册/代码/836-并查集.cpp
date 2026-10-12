// 输入 n、m；M a b 合并，Q a b 查询是否同集合，输出 Yes/No。
#include <iostream>
#include <vector>
#include <numeric>
#include <utility>
using namespace std;
struct DSU {
    vector<int> p, sz;
    explicit DSU(int n):p(n+1),sz(n+1,1){iota(p.begin(),p.end(),0);}
    int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
    void merge(int a,int b){
        a=find(a); b=find(b); if(a==b)return;
        if(sz[a]<sz[b])swap(a,b);
        p[b]=a; sz[a]+=sz[b]; // 大小只维护在根节点。
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;if(!(cin>>n>>m)||n<1||m<0)return 1;
    DSU d(n);
    while(m--){char op;int a,b;cin>>op>>a>>b;
        if(a<1||a>n||b<1||b>n)return 1;
        if(op=='M')d.merge(a,b);
        else if(op=='Q')cout<<(d.find(a)==d.find(b)?"Yes":"No")<<'\n';
        else return 1;
    }
}
