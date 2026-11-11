#include <bits/stdc++.h>
#define int long long
using namespace std;

double a,b,c,d;
vector<double> roots;
double f(double x)
{
    return ((a*x+b)*x+c)*x+d;
}
signed main()
{
    cin>>a>>b>>c>>d;
    // 单独收集整点根，含-100和100。
    for(int i=-100;i<=100;i++)
    {
        if(fabs(f(i))<1e-9) roots.push_back(i);
    }
    for(int i=-100;i<100;i++)
    {
        double l=i,r=i+1,fl=f(l),fr=f(r);
        if(fabs(fl)<1e-9||fabs(fr)<1e-9) continue;
        if((fl>0)==(fr>0)) continue;
        for(int j=1;j<=60;j++)
        {
            double mid=(l+r)/2,fm=f(mid);
            if((fl>0)==(fm>0))
            {
                l=mid;
                fl=fm;
            }
            else r=mid;
        }
        roots.push_back((l+r)/2);
    }
    sort(roots.begin(),roots.end());
    vector<double> ans;
    for(double x:roots)
    {
        if(fabs(x)<1e-8) x=0;
        if(ans.empty()||fabs(x-ans.back())>1e-6) ans.push_back(x);
    }
    for(int i=0;i<(int)ans.size();i++)
        cout<<fixed<<setprecision(2)<<ans[i]<<(i+1==(int)ans.size()?'\n':' ');
    return 0;
}
