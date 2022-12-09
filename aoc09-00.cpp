#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

inline void drag(pair<int, int> &t, pair<int, int> &h) {
    int dx = t.first - h.first, dy = t.second - h.second;
    if (abs(dx) < 2 && abs(dy) < 2) return;
    if (dx) h.first += dx / abs(dx);
    if (dy) h.second += dy / abs(dy);
}

vector< pair<int, int> > step[10];

int calc(int k) {
    pair<int, int> h = {0, 0}, t = {0, 0};
    set< pair<int, int> > s;
    s.insert(h);

    for (int i = 0; i < step[k].size(); i ++) {
        auto d = step[k][i];
        t.first += d.first, t.second += d.second;
        auto th = h;
        drag(t, th);
        if (th != h) step[k + 1].push_back({th.first - h.first, th.second - h.second});
        h = th;
        s.insert(h);
    }

    return s.size();
}

int main() {
    freopen("09.in", "r", stdin);
    freopen("09.out", "w", stdout);
    int _step;
    char o;
    while (cin>>o>>_step) {
        while (_step --) {
            if (o == 'L') step[0].push_back({-1, 0});
            if (o == 'R') step[0].push_back({1, 0});
            if (o == 'U') step[0].push_back({0, -1});
            if (o == 'D') step[0].push_back({0, 1});
        }
    }
    for (int i = 1; i <= 8; i ++) calc(i);
    cout<<calc(9)<<endl;
    return 0;
}