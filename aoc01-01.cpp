#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    freopen("01.in", "r", stdin);
    freopen("01.out", "w", stdout);
    int t = 0, cur = 0;
    int ans[3] = {0, 0, 0};
    char prev = '\n';
    while (true) {
        char c = getchar();
        if (c == '\n' || c == EOF) {
            t += cur;
            cur = 0;
            if (prev == '\n' || c == EOF) {
                if (t > ans[0]) ans[0] = t;
                sort(ans, ans + 3);
                t = 0;
            }
            if (c == EOF) {
                break;
            }
        } else {
            cur = cur * 10 + c - 48;
        }
        prev = c;
    }
    printf("%d\n", ans[0] + ans[1] + ans[2]);
    return 0;
}