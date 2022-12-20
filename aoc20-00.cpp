#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> a;
int n = 0;

inline int find(int x) {
    for (int i = 0; i < a.size(); i ++)
        if (a[i].second == x) return i;
    throw 0;
}

inline int move(int pos) {
    if (a[pos].first == 0) return pos;
    int step = abs(a[pos].first), d = a[pos].first / step;
    while (step --) {
        pos = pos + d;
        if (pos == n) pos = 1;
        if (pos == -1) pos = n - 2;
    }
    return pos;
}

int main() {
    freopen("20.in", "r", stdin);
    freopen("20.out", "w", stdout);
    int x;
    while (cin >> x) a.push_back({x, n ++});

    for (int i = 0; i < n; i ++) {
        int pos = find(i);
        int dest = move(pos);
        if (pos == dest) continue;        
        auto t = a[pos];
        if (dest > pos) {
            for (int j = pos; j < dest; j ++) a[j] = a[j + 1];
        }
        if (dest < pos) {
            for (int j = pos; j > dest; j --) a[j] = a[j - 1];
        }
        a[dest] = t;
    }

    int ans = 0;
    for (int i = 0; i < n; i ++)
        if (a[i].first == 0) {
            ans = a[(i + 1000) % n].first + a[(i + 2000) % n].first + a[(i + 3000) % n].first;
            break;
        }

    cout<<ans<<endl;

    return 0;
}
