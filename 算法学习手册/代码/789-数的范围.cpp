// 输入 n、q，有序数组及 q 个目标；每行输出从0计的首尾位置，未找到输出-1 -1。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; if(!(cin>>n>>q) || n<0 || q<0) return 1;
    vector<long long>a(n); for(auto&x:a)cin>>x;
    while(q--) {
        long long x; cin>>x;
        auto l=lower_bound(a.begin(),a.end(),x);
        if(l==a.end()||*l!=x) cout<<"-1 -1\n";
        else cout<<(l-a.begin())<<' '<<(upper_bound(l,a.end(),x)-a.begin()-1)<<'\n';
    }
}
