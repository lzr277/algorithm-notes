#include <iostream>
using namespace std;
int main() {
    int n; cin >> n;
    long long c[19]{}; c[0]=1;
    for(int i=1;i<=n;++i)
        for(int k=0;k<i;++k) c[i]+=c[k]*c[i-1-k];
    cout << c[n] << '\n';
}
