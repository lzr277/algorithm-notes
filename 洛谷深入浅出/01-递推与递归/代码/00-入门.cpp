#include <iostream>
using namespace std;
long long memo[91]{};
bool seen[91]{};
long long fact(int n) { return n==0?1:n*fact(n-1); }
long long fib(int n) { return n<=1?n:fib(n-1)+fib(n-2); }
long long fibMemo(int n) {
    if(n<=1) return n;
    if(seen[n]) return memo[n];
    memo[n]=fibMemo(n-1)+fibMemo(n-2);
    seen[n]=true; return memo[n];
}
long long fibLoop(int n) {
    if(n<=1) return n;
    long long a=0,b=1;
    for(int i=2;i<=n;++i) { long long next=a+b; a=b; b=next; }
    return b;
}
int main() {
    int n; cin>>n; // 为同时运行所有演示，本程序限定 0..20
    if(n<0 || n>20) { cerr<<"请输入 0..20\n"; return 1; }
    long long sum=0;
    for(int i=1;i<=n;++i) sum+=i;
    cout<<sum<<'\n'<<fact(n)<<'\n'<<fib(n)<<'\n'<<fibMemo(n)<<'\n'<<fibLoop(n)<<'\n';
}
