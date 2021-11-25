#include <bits/stdc++.h>

int* a = new int [5];
int main() {
    a[0] = 5;
    a[1] = 2;
    a[2] = 4;
    a[3] = 9;
    a[4] = 0;
    std::sort(a, a + 5);
    for(int i = 0; i < 5; i++) {
        std::cout<<a[i]<<" ";
    }
}