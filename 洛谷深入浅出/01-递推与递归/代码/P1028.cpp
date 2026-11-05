#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n; cin >> n;
    vector<long long> f(n+1,0);
    for(int i=1;i<=n;++i) {
        f[i]=1; // 只保留当前数，立即停止
        for(int k=1;k<=i/2;++k) f[i]+=f[k];
    }
    cout << f[n] << '\n';
}
