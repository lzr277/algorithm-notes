// 补充的完整程序。输入 n 与 n 个整数；输出升序结果。GNU C++17。
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
void quick_sort(vector<long long>& a, int l, int r) {
    if (l >= r) return;
    long long pivot = a[l + (r-l)/2];
    int i=l-1, j=r+1;
    while (i<j) {
        do { ++i; } while(a[i]<pivot);
        do { --j; } while(a[j]>pivot);
        if(i<j) swap(a[i],a[j]);
    }
    quick_sort(a,l,j);
    quick_sort(a,j+1,r);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n) || n<0) return 1;
    vector<long long> a(n); for(auto& x:a) cin>>x;
    quick_sort(a,0,n-1);
    for(int i=0;i<n;++i) cout<<(i?" ":"")<<a[i];
    cout<<'\n';
}
