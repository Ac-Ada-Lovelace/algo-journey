#include "bits/stdc++.h"

using namespace std;

bool is_period(string s, int p) {
  auto p_string = s.substr(0, p);

  int times = s.length() / p;
  int flag = 0;
  for (int i = 0; i < times; i++) {
    if (s.substr(i * p, p) != p_string) {
      flag = 1;
      break;
    }
  }

  return !flag;
}

int try_p(string s) {
  for (int i = 1; i < s.length(); i++) {
    if (s.length() % i == 0) {
      if (is_period(s, i)) {
        return i;
      }
    }
  }
}

int main() {
  string s = "abcabcabcabc";
  cout << try_p(s) << endl;
}
