#include <bits/stdc++.h>
using namespace std;

// 验证答案是否正确
int gates[20];
int input_val[10];
int m;

int get_val(int g, int x, vector<int>& cache) {
    if (cache[g] != -1) return cache[g];

    int l = gates[2*g-1];
    int r = gates[2*g];

    int li = (l > 0) ? get_val(l, x, cache) : input_val[-l];
    int ri = (r > 0) ? get_val(r, x, cache) : input_val[-r];

    cache[g] = !(li && ri);
    return cache[g];
}

int test_circuit(int x) {
    vector<int> cache(m+1, -1);
    return get_val(m, x, cache);
}

int main() {
    // 读入电路
    int n = 3;
    m = 6;

    // -1 -3 -1 -2 1 2 1 2 4 3 5 5
    gates[1] = -1; gates[2] = -3;
    gates[3] = -1; gates[4] = -2;
    gates[5] = 1;  gates[6] = 2;
    gates[7] = 1;  gates[8] = 2;
    gates[9] = 4;  gates[10] = 3;
    gates[11] = 5; gates[12] = 5;

    // 测试所有输入都是x的情况
    cout << "=== 原始电路（所有输入都是x） ===" << endl;
    input_val[1] = 0; input_val[2] = 0; input_val[3] = 0;
    int orig_f0 = test_circuit(0);
    input_val[1] = 1; input_val[2] = 1; input_val[3] = 1;
    int orig_f1 = test_circuit(1);
    cout << "f(0) = " << orig_f0 << ", f(1) = " << orig_f1 << endl;

    // 测试答案 10x
    cout << "\n=== 测试答案 10x ===" << endl;
    input_val[1] = 1;  // 常量1
    input_val[2] = 0;  // 常量0
    // input_val[3] = x
    input_val[3] = 0;
    int ans1_f0 = test_circuit(0);
    input_val[3] = 1;
    int ans1_f1 = test_circuit(1);
    cout << "f(0) = " << ans1_f0 << ", f(1) = " << ans1_f1 << endl;
    cout << "正确？" << (ans1_f0 == orig_f0 && ans1_f1 == orig_f1 ? "YES" : "NO") << endl;

    // 测试答案 x11
    cout << "\n=== 测试答案 x11 ===" << endl;
    input_val[2] = 1;  // 常量1
    input_val[3] = 1;  // 常量1
    // input_val[1] = x
    input_val[1] = 0;
    int ans2_f0 = test_circuit(0);
    input_val[1] = 1;
    int ans2_f1 = test_circuit(1);
    cout << "f(0) = " << ans2_f0 << ", f(1) = " << ans2_f1 << endl;
    cout << "正确？" << (ans2_f0 == orig_f0 && ans2_f1 == orig_f1 ? "YES" : "NO") << endl;

    return 0;
}
