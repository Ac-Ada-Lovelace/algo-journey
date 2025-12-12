#include <bits/stdc++.h>
using namespace std;

int lx, rx;
vector<pair<int, int>> segs;
int n1, p1;
int v;

int expand(int li, int ri) {
    if(segs[ri].first - segs[li].first == 2){
        return 2*1;
    }
    int lmi;
    for(lmi = li; lmi < li; lmi++){
        if(segs[lmi].second> segs[li].second) break;
    }
    int rmi;
    for(int rmi = ri; rmi > li; rmi--){
        if(segs[rmi].second> segs[ri].second) break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cin >> lx >> rx;
        if (lx == 0 && rx == 0)
            break;

        int cnt = 0;
        for (int i = lx; i <= rx; i += 2) {
            if (i == -1) {
                n1 = cnt;
            }
            if (i == 1) {
                p1 = cnt;
            }
            int h;
            cin >> h;
            segs.push_back({i, h});

            cnt++;
        }
    }
}
