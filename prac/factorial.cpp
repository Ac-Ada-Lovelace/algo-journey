#include "bits/stdc++.h"

using namespace std;

// 原有的三变量迭代版本
int fibonacci_3var(int n) {
  int n1 = 1, n2 = 1, n3 = 2;
  int state = 3;

  if (n <= 3) {
    return (n == 1) ? n1 : (n == 2) ? n2 : n3;
  }

  for (int i = 4; i <= n; i++) {
    switch (state) {
    case 1:
      n2 = n1 + n3;
      state = 2;
      break;
    case 2:
      n3 = n1 + n2;
      state = 3;
      break;
    case 3:
      n1 = n2 + n3;
      state = 1;
      break;
    }
  }

  return (state == 1) ? n1 : (state == 2) ? n2 : n3;
}

// 备忘录递归版本
unordered_map<int, int> memo;

int fibonacci_memo(int n) {
  if (n <= 2) {
    return 1;
  }
  
  // 如果已经计算过，直接返回
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }
  
  // 递归计算并存储结果
  memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
  return memo[n];
}

int main() {
  cout << "三变量迭代版本: ";
  for (int i = 1; i <= 100; i++) {
    cout << fibonacci_3var(i) << " ";
  }
  cout << endl;
  
  cout << "备忘录递归版本: ";
  memo.clear(); // 清空备忘录
  for (int i = 1; i <= 100; i++) {
    cout << fibonacci_memo(i) << " ";
  }
  cout << endl;
}