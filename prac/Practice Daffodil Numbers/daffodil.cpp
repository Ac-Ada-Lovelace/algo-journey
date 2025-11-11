#include "bits/stdc++.h"


using namespace std;

// 整数幂运算（避免浮点运算）
int int_pow(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

bool is_daffodil(int num, int digits) {
  int original = num;
  int sum = 0;

  while (num > 0) {
    int digit = num % 10;
    sum += int_pow(digit, digits);
    num /= 10;
  }

  return sum == original;
}

int main(int argc, const char** argv) {
  // 三位数水仙花数，digits 固定为 3
  for (int i = 100; i <= 999; i++) {
    if (is_daffodil(i, 3)) {
      cout << i << " ";
    }
  }
  cout << endl;
  return 0;
}