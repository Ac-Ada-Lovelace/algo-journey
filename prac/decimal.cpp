#include "bits/stdc++.h"

using namespace std;

void divide_decimal(int dividend, int divisor, int ans[], int prec) {
  for (int p = 0; p <= prec; p++) {
    if (dividend == divisor) {
      ans[p] = 1;
      break;
    }
    if (dividend < divisor) {
      ans[p] = 0;
      dividend = dividend * 10;
    } else {
      ans[p] = dividend / divisor;
      dividend = (dividend % divisor) * 10;
    }
  }
}

void print_decimal(int ans[], int prec) {
  cout << "0.";
  for (int i = 0; i <= prec; i++) {
    cout << ans[i];
  }
  cout << endl;
}

int main() {

  int ans[10] = {0};  // 初始化为 0，方便调试时查看
  divide_decimal(1, 3, ans, 9);
  print_decimal(ans, 3);
}
