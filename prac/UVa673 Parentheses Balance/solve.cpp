#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    string line;
    if (!(cin >> t)) return 0;
    getline(cin, line);  // consume rest of first line

    while (t--) {
        getline(cin, line);
        stack<char> st;
        bool ok = true;
        for (char ch : line) {
            if (ch == '(' || ch == '[') {
                st.push(ch);
            } else if (ch == ')' || ch == ']') {
                if (st.empty()) { ok = false; break; }
                char top = st.top();
                st.pop();
                if (ch == ')' && top != '(') { ok = false; break; }
                if (ch == ']' && top != '[') { ok = false; break; }
            }
        }
        if (!st.empty()) ok = false;
        cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}
