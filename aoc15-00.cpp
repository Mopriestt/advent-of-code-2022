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

const int target = 2000000;
//const int target = 10;

inline bool intersect(pair<int, int> &a, pair<int, int> &b) {
    return !(a.second < b.first || a.first > b.second);
}

int main() {
    freopen("15.in", "r", stdin);
    freopen("15.out", "w", stdout);

    int x, y, bx, by, ans = 0;
    vector<pair<int, int>> segs;
    set<int> b;
    char fmt[] = "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n";
    while (~scanf(fmt, &x, &y, &bx, &by)) {
        auto seg = calc(x, y, bx, by, target);
        if (by == target) b.insert(bx);
        if (seg.first <= seg.second) segs.push_back(seg);
    }
    sort(segs.begin(), segs.end());
    for (int i = 0; i < segs.size(); i ++) {
        if (i < segs.size() - 1 && intersect(segs[i], segs[i + 1])) {
            segs[i + 1].first = min(segs[i].first, segs[i + 1].first);
            segs[i + 1].second = max(segs[i].second, segs[i + 1].second);
        }
        else {
            ans += segs[i].second - segs[i].first + 1;
            for (int x : b)
                if (segs[i].first <= x && segs[i].second >= x) -- ans;
        }
    }
    cout<<ans<<endl;
    return 0;
}