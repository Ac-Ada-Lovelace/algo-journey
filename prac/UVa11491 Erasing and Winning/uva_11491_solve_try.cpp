// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=2486
// UVa11491 Erasing and Winning
#include <bits/stdc++.h>
using namespace std;

int N, D;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    while (true) {
        cin >> N >> D;
        if (N == 0 && D == 0)
            break;

        stack<char> nums;
        char nn;
        cin >> nn;
        nums.push(nn);
        while (D > 0 && cin >> nn) {
            if (nn > nums.top()) {
                nums.pop();
                D--;
                nums.push(nn);
            } else {
                nums.push(nn);
            }
        }
        if(D==0){
            while(cin>>nn){
                nums.push(nn);
            }
        }
        stack<char> rev;
        while(!nums.empty()){
            rev.push(nums.top());
            nums.pop();
        }
        string numstr;
        while(!rev.empty()){
            numstr.push_back(rev.top());
            rev.pop();
        }
        numstr = numstr.substr(0, numstr.size()-D);
        cout<< numstr << "\n";
    }
}
