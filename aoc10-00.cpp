#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    freopen("10.in", "r", stdin);
    freopen("10.out", "w", stdout);
    string s;
    vector<int> a;
    
    while (cin>>s) {
        a.push_back(0);
        if (s[0] == 'a') {
            int x = 0;
            cin>>x;
            a.push_back(x);
        }
    }

    int cpu = 1, ans = 0;
    for (int i = 0; i < a.size(); i ++) {
        if ((i - 19) % 40 == 0) ans += cpu * (i + 1);
        cpu += a[i];
    }

    cout<<ans<<endl;
    return 0;
}