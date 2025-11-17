#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int matrix_count;
  if (!(cin >> matrix_count)) return 0;

  array<pair<int, int>, 26> matrices{};
  vector<bool> has_matrix(26, false);
  for (int i = 0; i < matrix_count; ++i) {
    char name;
    int rows, cols;
    cin >> name >> rows >> cols;
    matrices[name - 'A'] = {rows, cols};
    has_matrix[name - 'A'] = true;
  }

  string expr;
  while (cin >> expr) {
    stack<pair<int, int>> st;
    long long ops = 0;
    bool ok = true;

    for (char ch : expr) {
      if (ch == '(') continue;
      if (isalpha(ch)) {
        if (!has_matrix[ch - 'A']) {
          ok = false;
          break;
        }
        st.push(matrices[ch - 'A']);
        continue;
      }
      if (ch == ')') {
        if (st.size() < 2) {
          ok = false;
          break;
        }
        auto right = st.top();
        st.pop();
        auto left = st.top();
        st.pop();
        if (left.second != right.first) {
          ok = false;
          break;
        }
        ops += 1LL * left.first * left.second * right.second;
        st.push({left.first, right.second});
      }
    }

    if (!ok) {
      cout << "error\n";
    } else {
      cout << ops << "\n";
    }
  }
  return 0;
}
