#include "bits/stdc++.h"

using namespace std;

// 原子量映射表
map<string, double> atomic_mass = {
    {"C", 12.01},
    {"H", 1.008},
    {"O", 16.00},
    {"N", 14.01}
};

double calculate_molar_mass(string formula) {
    double total_mass = 0.0;
    int n = formula.length();
    
    for (int i = 0; i < n; ) {
        // 1. 读取元素符号
        string element = "";
        element += formula[i++];  // 大写字母
        
        // 如果后面跟着小写字母，也是元素符号的一部分
        if (i < n && islower(formula[i])) {
            element += formula[i++];
        }
        
        // 2. 读取数字（原子个数）
        int count = 0;
        while (i < n && isdigit(formula[i])) {
            count = count * 10 + (formula[i] - '0');
            i++;
        }
        
        // 如果没有数字，默认为 1
        if (count == 0) {
            count = 1;
        }
        
        // 3. 累加分子量
        total_mass += atomic_mass[element] * count;
    }
    
    return total_mass;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        string formula;
        cin >> formula;
        
        double mass = calculate_molar_mass(formula);
        
        // 输出保留 3 位小数
        cout << fixed << setprecision(3) << mass << endl;
    }
    
    return 0;
}