#include <bits/stdc++.h>
using namespace std;

int parse_num(const string& expr, int& pos) {
    int num = 0;
    while (pos < expr.size() && isdigit(expr[pos])) {
        num = num * 10 + (expr[pos] - '0');
        pos++;
    }
    return num;
}

int parse_mul(const string& expr, int& pos) {
    int result = parse_num(expr, pos);
    while (pos < expr.size() && expr[pos] == '*') {
        pos++;
        result *= parse_num(expr, pos);
    }
    return result;
}

int evaluate(const string& expr) {
    int pos = 0;
    int result = parse_mul(expr, pos);

    while (pos < expr.size()) {
        char op = expr[pos];
        pos++;
        int next_val = parse_mul(expr, pos);

        if (op == '+')
            result += next_val;
        else if (op == '-')
            result -= next_val;
    }

    return result;
}

void dfs(int pos, const string& digits, string& expr, string& last_num,
         set<string>& solutions) {
    if (pos == digits.size()) {
        if (evaluate(expr) == 2000) {
            solutions.insert(expr);
        }
        return;
    }

    char digit = digits[pos];

    // 选择1-3：插入运算符
    for (char op : {'+', '-', '*'}) {
        expr += op;
        expr += digit;
        string old_last = last_num;
        last_num = string(1, digit);

        dfs(pos + 1, digits, expr, last_num, solutions);

        // 回溯
        last_num = old_last;
        expr.pop_back();
        expr.pop_back();
    }

    // 选择4：连接数字（前导零剪枝）
    if (last_num != "0") {
        expr += digit;
        last_num += digit;

        dfs(pos + 1, digits, expr, last_num, solutions);

        // 回溯
        last_num.pop_back();
        expr.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    int case_num = 1;

    while (getline(cin, line)) {
        size_t pos = line.find('=');
        if (pos != string::npos) {
            line = line.substr(0, pos);
        }

        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        if (line.empty())
            break;

        set<string> solutions;
        string expr(1, line[0]);
        string last_num(1, line[0]);
        dfs(1, line, expr, last_num, solutions);

        cout << "Problem " << case_num++ << "\n";
        if (solutions.empty()) {
            cout << "  IMPOSSIBLE\n";
        } else {
            for (const string& sol : solutions) {
                cout << "  " << sol << "=\n";
            }
        }
    }

    return 0;
}
