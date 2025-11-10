#include "bits/stdc++.h"

using namespace std;

int facotrial_3var(int n) {
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


int main(){
    for(int i=1;i<=10;i++){
        cout<<facotrial_3var(i)<<" ";
    }
}