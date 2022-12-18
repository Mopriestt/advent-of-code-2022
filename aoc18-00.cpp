#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline bool connect(vector<int> &a, vector<int> &b) {
    int zero = 0, one = 0;
    for (int i = 0; i < 3; i ++) {
        if (abs(a[i] - b[i]) == 0) ++ zero;
        if (abs(a[i] - b[i]) == 1) ++ one;
    }
    return zero == 2 && one == 1;
}

int main() {
    freopen("18.in", "r", stdin);
    freopen("18.out", "w", stdout);
    vector< vector<int> > a;
    int x, y, z;
    while (~scanf("%d,%d,%d", &x, &y, &z))
        a.push_back({x, y, z});
    int n = a.size();

    int ct = 0;
    for (int i = 0; i < n; i ++)
        for (int j = i + 1; j < n; j ++) {
            if (connect(a[i], a[j])) ++ ct;
        }
    cout << n * 6 - ct * 2 << endl;
    return 0;
}
