#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> c;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        int x = carry;
        if (i < a.size()) x += a[i];
        if (i < b.size()) x += b[i];
        c.push_back(x % 10);
        carry = x / 10;
    }
    return c;
}
int main() {
    int n; cin >> n;
    vector<int> a{1}, b{1}; // f[0], f[1]
    for (int i = 2; i <= n; ++i) {
        auto c = add(a, b);
        a = b; b = c;
    }
    for (auto it = b.rbegin(); it != b.rend(); ++it) cout << *it;
    cout << '\n';
}
