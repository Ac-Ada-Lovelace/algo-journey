// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=4008
// UVa12563 Jin Ge Jin Qu hao
#include <bits/stdc++.h>
using namespace std;

struct song{
    int id;
    int times;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >>T;
    for(int t = 1; t <= T; t++){
        int songs_count, limited_time;
        cin >> songs_count >> limited_time;

        vector<int> songs(songs_count);
        for(int i = 0; i < songs_count; i++){
            cin >> songs[i];
        }


    }

}
