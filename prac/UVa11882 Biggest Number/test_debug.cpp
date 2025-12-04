#include <bits/stdc++.h>
using namespace std;

int main() {
    string grid[3] = {"##9784#", "##123##", "##45###"};
    
    cout << "Grid visualization:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nNon-# positions:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (grid[i][j] != '#') {
                cout << "(" << i << "," << j << ")=" << grid[i][j] << " ";
            }
        }
    }
    cout << endl;
    
    return 0;
}
