#include <iostream>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

int main() {
    freopen("03.in", "r", stdin);
    freopen("03.out", "w", stdout);
    string a, b, c;
    int ans = 0;
    while (cin>>a>>b>>c) {
        set<char> A(a.begin(), a.end()), B(b.begin(), b.end()), C(c.begin(), c.end());
        for (char c = 'a'; c <= 'z'; c ++) {
            if (A.find(c) != A.end() && B.find(c) != B.end() && C.find(c) != C.end()) ans += c - 'a' + 1;
        }
        for (char c = 'A'; c <= 'Z'; c ++) {
            if (A.find(c) != A.end() && B.find(c) != B.end() && C.find(c) != C.end()) ans += c - 'A' + 27;
        }
    }
    cout<<ans<<endl;
    return 0;
}