#include <bits/stdc++.h>
using namespace std;

int main() {
    // 生成大测试数据
    cout << 1 << '\n';
    int n = 1000000;
    cout << n << '\n';
    
    for (int i = 0; i < n; i++) {
        cout << (i % 100000) << '\n';  // 制造重复
    }
    
    return 0;
}
