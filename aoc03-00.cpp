#include <iostream>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

int main() {
    freopen("03.in", "r", stdin);
    freopen("03.out", "w", stdout);
    string s;
    int ans = 0;
    while (cin>>s) {
        set<char> hash;
        for (int i = 0; i < s.size() / 2; i ++) {
            hash.insert(s[i]);
        }
        for (int i = s.size() / 2; i < s.size(); i ++)
            if (hash.find(s[i]) != hash.end()) {
                ans += s[i] <= 'Z' ? s[i] - 'A' + 27 : s[i] - 'a' + 1;
                break;
            }
    }
    cout<<ans<<endl;
    return 0;
}