#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);

    freopen("output.txt", "w", stdout);
    int cases;
    cin >> cases;
    cin.ignore();
    while(cases--){
        string line;
        getline(cin, line);
        stringstream ss(line);
        stack<char> s;
        char c;
        while(ss >> c){
            switch(c){
                case '(':
                case '[':
                    s.push(c);
                    break;
                case ')':
                    if(s.empty() || s.top() != '('){
                        s.push(c); // mark as unbalanced
                    } else {
                        s.pop();
                    }
                    break;
                case ']':
                    if(s.empty() || s.top() != '['){
                        s.push(c); // mark as unbalanced
                    } else {
                        s.pop();
                    }
                    break;
            }
        }
        

    }
    
}
