// 补充程序：n、n个闭区间左右端点；求覆盖每个区间至少一次的最少点数。
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n)||n<0)return 1;
    vector<pair<long long,long long>>a(n);
    for(auto&[l,r]:a){cin>>l>>r;if(l>r)return 1;}
    sort(a.begin(),a.end(),[](const auto&x,const auto&y){return x.second<y.second;});
    bool selected=false;long long last=0;int count=0;
    for(auto[l,r]:a)if(!selected||l>last){last=r;selected=true;++count;}
    cout<<count<<'\n';
}
