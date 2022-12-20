#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int multiplier = 811589153;

vector<pair<long long, int>> a;
int n = 0;

inline int find(int x) {
    for (int i = 0; i < a.size(); i ++)
        if (a[i].second == x) return i;
    throw 0;
}

inline int move(int pos) {
    if (a[pos].first == 0) return pos;
    int step = abs(a[pos].first) % (n - 1);
    
    int d = a[pos].first > 0 ? 1 : -1;
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
    while (cin >> x) a.push_back({1LL * x * multiplier, n ++});

    for (int _ = 0; _ < 10; _ ++) {
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
    }

    long long ans = 0;
    for (int i = 0; i < n; i ++)
        if (a[i].first == 0) {
            ans = a[(i + 1000) % n].first + a[(i + 2000) % n].first + a[(i + 3000) % n].first;
            break;
        }

    cout<<ans<<endl;

    return 0;
}
