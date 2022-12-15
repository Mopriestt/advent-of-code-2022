#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

inline pair<int, int> calc(int x, int y, int bx, int by, int target) {
    int dist = abs(x - bx) + abs(y - by);
    int l = x - dist, r = x + dist;
    l += abs(y - target);
    r -= abs(y - target);
    return {l, r};
}

const int target = 4000000;
//const int target = 20;

inline bool intersect(pair<int, int> &a, pair<int, int> &b) {
    return !(a.second < b.first || a.first > b.second);
}

int x[30], y[30], bx[30], by[30], n = 0;
bool hasAnswer(int line) {
    vector<pair<int, int>> segs, non_inter_segs;
    for (int i = 0; i < n; i ++) {
        auto seg = calc(x[i], y[i], bx[i], by[i], line);
        seg.first = max(0, seg.first);
        seg.second = min(target, seg.second);
        if (by[i] == line && bx[i] <= target && bx[i] >= 0) segs.push_back({bx[i], bx[i]});
        if (seg.first <= seg.second) segs.push_back(seg);
    }
    sort(segs.begin(), segs.end());
    int ans = 0;
    for (int i = 0; i < segs.size(); i ++) {
        if (i < segs.size() - 1 && intersect(segs[i], segs[i + 1])) {
            segs[i + 1].first = min(segs[i].first, segs[i + 1].first);
            segs[i + 1].second = max(segs[i].second, segs[i + 1].second);
        }
        else {
            ans += segs[i].second - segs[i].first + 1;
            non_inter_segs.push_back(segs[i]);
        }
    }
    if (ans != target + 1) {
        for (int i = 0; i <= target; i ++) {
            bool has = false;
            for (int j = 0; j < non_inter_segs.size() && !has; j ++) {
                if (non_inter_segs[j].first <= i && non_inter_segs[j].second >= i) has = true;
            }
            if (!has) {
                cout<<1LL * i * 4000000 + line<<endl;
                return true;
            }
        }
        cout<<"Not Found"<<endl;
        throw;
    }
    return false;
}

int main() {
    freopen("15.in", "r", stdin);
    freopen("15.out", "w", stdout);

    char fmt[] = "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n";
    while (~scanf(fmt, x + n, y + n, bx + n, by + n)) ++ n;
    ++ n;

    for (int i = 0; i <= target; i ++) {
        if (hasAnswer(i)) return 0;
    }
    return 0;
}