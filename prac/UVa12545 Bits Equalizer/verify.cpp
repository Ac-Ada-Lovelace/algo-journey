// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=3990
// UVa12545 Bits Equalizer - Verified Solution
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s, target;
        cin >> s >> target;
        int n = s.size();

        // Count different cases
        // A: positions where s[i]='1' but target[i]='0'
        // B: positions where s[i]='0' but target[i]='1'
        // C: positions where s[i]='?' and target[i]='1'
        // D: positions where s[i]='?' and target[i]='0'
        int A = 0, B = 0, C = 0, D = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1' && target[i] == '0') {
                A++;
            } else if (s[i] == '0' && target[i] == '1') {
                B++;
            } else if (s[i] == '?' && target[i] == '1') {
                C++;
            } else if (s[i] == '?' && target[i] == '0') {
                D++;
            }
        }

        // Check if transformation is possible
        // We need to turn A '1's into '0's, but we can only do this by swapping
        // So we need at least A positions that need to become '1'
        // These can be B (0->1) or C (?->1)
        if (A > B + C) {
            cout << "Case " << t << ": " << -1 << '\n';
            continue;
        }

        int ans = 0;

        // Step 1: Swap '1's that need to become '0' with '0's that need to become '1'
        // This is optimal because one swap fixes two positions
        int swaps = min(A, B);
        ans += swaps;
        A -= swaps;
        B -= swaps;

        // Step 2: Remaining A (1->0) must swap with C (?->1)
        // After swap: position with '1' gets '?', position with '?' gets '1'
        // The '?' at target '0' position still needs to be set to '0'
        // Cost: 1 for swap + 1 for setting '?' to '0' = 2 operations per swap
        ans += 2 * A;
        C -= A;
        A = 0;

        // Step 3: Remaining B (0->1) needs one operation (change 0 to 1)
        ans += B;
        B = 0;

        // Step 4: All remaining ?'s need one operation each (either ?->0 or ?->1)
        ans += C + D;

        cout << "Case " << t << ": " << ans << '\n';
    }
}
