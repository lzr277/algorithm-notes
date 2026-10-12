// 输入测试数，然后每组 a、k、p。0<=k，1<=p<=INT_MAX；a是long long范围。
#include <iostream>
#include <climits>
using namespace std;
long long mod_pow(long long a,unsigned long long k,long long p){
    a%=p;if(a<0)a+=p;
    long long res=1%p;
    while(k){if(k&1ULL)res=res*a%p;a=a*a%p;k>>=1;}
    return res;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int t;if(!(cin>>t)||t<0)return 1;
    while(t--){long long a,p;unsigned long long k;cin>>a>>k>>p;
        if(p<1||p>INT_MAX)return 1;
        cout<<mod_pow(a,k,p)<<'\n';
    }
}
