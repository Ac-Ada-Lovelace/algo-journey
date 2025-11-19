#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        int n;
        cin >> n;

        int indeg[26]{};
        int outdeg[26]{};
        array<array<int,26>,26> adj{};
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            int u = s.front() - 'a';
            int v = s.back() - 'a'; 
            outdeg[u]++;
            indeg[v]++;
        }

        int count = 2;
        for (int i = 0; i < 26; i++) {
            if (count < 0) {
                break;
            }
            if (indeg[i] == outdeg[i]) {
                continue;
            } else if (indeg[i] + 1 == outdeg[i] || indeg[i] == outdeg[i] + 1) {
                count--;
            } else {
                count = -1;
                break;
            }
        }
        if(count == 2 || count == 0){
            cout << "Ordering is possible" << endl;
        }else{
            cout << "The door cannot be opened" << endl;
        }
    }
}
