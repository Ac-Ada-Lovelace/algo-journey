#include "bits/stdc++.h"
using namespace std;

int calc_score(char *s, int l) {
  int score = 0;
  int state = 1;
  for (int i = 0; i < l; i++) {
    if (s[i] == 'O') {
      score += state;
      state++;

    } else {
      state = 1;
    }
  }

  return score;
}

int main() {
  char *s = "OOXXOXXOOO";
  cout << calc_score(s, strlen(s)) << endl;

  s = "OOO";

  cout << calc_score(s, strlen(s)) << endl;
}
