#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    freopen("01.in", "r", stdin);
    freopen("01.out", "w", stdout);
    int ans = 0, t = 0, cur = 0;
    char prev = '\n';
    while (true) {
        char c = getchar();
        if (c == '\n' || c == EOF) {
            t += cur;
            cur = 0;
            if (prev == '\n' || c == EOF) {
                ans = max(ans, t);
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
    printf("%d\n", ans);
    return 0;
}