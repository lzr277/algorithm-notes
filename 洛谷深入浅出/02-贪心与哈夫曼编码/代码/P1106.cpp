#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    string s;
    int k;
    cin>>s>>k;
    while(k--)
    {
        int pos=0;
        while(pos+1<(int)s.size()&&s[pos]<=s[pos+1]) pos++;
        s.erase(pos,1);
    }
    int pos=0;
    while(pos<(int)s.size()&&s[pos]=='0') pos++;
    if(pos==(int)s.size()) cout<<0;
    else cout<<s.substr(pos);
    cout<<'\n';
    return 0;
}
