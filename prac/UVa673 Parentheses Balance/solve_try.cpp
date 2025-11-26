// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=103&page=show_problem&problem=614
// UVa673 Parentheses Balance
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int cases;
    cin >> cases;
    cin.ignore();
    while (cases--) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        if (line.empty()) {
            cout << "Yes" << endl;
            continue;
        }

        stack<char> stk;
        char sym;
        int flag = 0;
        while (ss >> sym) {
            if (sym == '(' || sym == '[') {
                stk.push(sym);
                continue;
            }
            if(stk.empty()) {
                flag = 1;
                break;
            }
            if (sym == ')' && stk.top() == '(') {
                stk.pop();
                continue;
            }
            if (sym == ']' && stk.top() == '[') {
                stk.pop();
                continue;
            }

            flag = 1;
            break;
        }

        if (flag || !stk.empty()) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
}
