#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    freopen("04.in", "r", stdin);
    freopen("04.out", "w", stdout);
    char s[100];
    int ans = 0;
    while (~scanf("%s", s)) {
        int a, b, x, y;
        sscanf(s, "%d-%d,%d-%d", &a, &b, &x, &y);
        if (a >= x && b <= y || x >= a && y <= b) ++ ans;
    }
    printf("%d\n", ans);
    return 0;
}