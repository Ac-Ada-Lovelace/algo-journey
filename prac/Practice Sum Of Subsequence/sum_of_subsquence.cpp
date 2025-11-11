#include "bits/stdc++.h"

using namespace std;

int main() {
  int n, m;
  int case_num = 1;
  
  while (cin >> n >> m && (n != 0 || m != 0)) {
    double sum = 0.0;
    
    // 关键：从 m 倒着加到 n
    // 先加小数，再加大数，减少精度损失
    for (int i = m; i >= n; i--) {
      sum += 1.0 / (i * i);
    }
    
    cout << "Case " << case_num++ << ": ";
    cout << fixed << setprecision(5) << sum << endl;
  }
  
  return 0;
}