#include "bits/stdc++.h"
using namespace std;

double quick_value[] = {12.01, 1.008, 16.00, 14.01};
int get_kind(char atom) {
  switch (atom) {
  case 'C':
    return 0;
  case 'H':
    return 1;
  case 'O':
    return 2;
  case 'N':
    return 3;
  default:
    return -1;
  }
}
int get_value(char atom) {
  switch (atom) {
  case 'C':
    return quick_value[0];
  case 'H':
    return quick_value[1];
  case 'O':
    return quick_value[2];
  case 'N':
    return quick_value[3];
  }
}
double calc_molar_mass(char *s, int l) {
  double res = 0;
  int state = 0;
  int kind = -1;
  int num = 0;
  for (int p = 0; p < l; p++) {
    if (state == 0) {
      kind = get_kind(s[p]);
      state = 1;
    }
    if (state == 1) {
    }
  }
}
