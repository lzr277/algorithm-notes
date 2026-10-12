// 补充程序：n、n个数；严格递增子序列最大长度，使用最小尾值+二分。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n)||n<0)return 1;
    vector<long long>tails;
    while(n--){long long x;cin>>x;auto it=lower_bound(tails.begin(),tails.end(),x);
        if(it==tails.end())tails.push_back(x);else *it=x;
    }
    cout<<tails.size()<<'\n';
}
