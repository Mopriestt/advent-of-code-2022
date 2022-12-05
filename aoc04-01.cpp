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
        ans ++;
        if (a > y || b < x) -- ans;
    }
    printf("%d\n", ans);
    return 0;
}