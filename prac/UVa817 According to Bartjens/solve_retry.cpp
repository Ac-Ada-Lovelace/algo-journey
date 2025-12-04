#include <bits/stdc++.h>
using namespace std;

long long evalExpr(const string& s) {
    long long res = 0;  // 当前已确定的总和
    long long last = 0; // 上一段乘除链的结果
    long long num = 0;  // 当前正在读取的数字
    char op = '+';      // 上一个运算符，默认 '+'

    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == ' ')
            continue;

        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }

        // 如果当前字符是运算符，或者到了字符串末尾，就要结算一次
        if (!isdigit(c) && c != ' ' || i == n - 1) {
            switch (op) {
                case '+':
                    res += last;
                    last = num;
                    break;
                case '-':
                    res += last;
                    last = -num;
                    break;
                case '*':
                    last = last * num;
                    break;
                case '/':
                    // C++ 默认对负数是向 0 取整，通常也是题目要求
                    last = last / num;
                    break;
            }
            op = c;  // 更新当前运算符
            num = 0; // 重置当前数字
        }
    }
    res += last; // 别忘了最后一段
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
