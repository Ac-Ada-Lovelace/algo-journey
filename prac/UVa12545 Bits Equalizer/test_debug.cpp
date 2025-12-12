// Debug specific test case
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s, target;
        cin >> s >> target;

        if (t == 6 || t == 9 || t == 13) {
            cout << "Case " << t << ":\n";
            cout << "  S = \"" << s << "\"\n";
            cout << "  T = \"" << target << "\"\n";

            int A = 0, B = 0, C = 0, D = 0;
            for (int i = 0; i < (int)s.size(); i++) {
                if (s[i] == '1' && target[i] == '0') A++;
                else if (s[i] == '0' && target[i] == '1') B++;
                else if (s[i] == '?' && target[i] == '1') C++;
                else if (s[i] == '?' && target[i] == '0') D++;
            }

            cout << "  A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";

            int ans = 0;
            int swaps = min(A, B);
            ans += swaps;
            A -= swaps;
            B -= swaps;
            cout << "  After swapping A with B: ans=" << ans << " A=" << A << " B=" << B << "\n";

            ans += A;
            C -= A;
            A = 0;
            cout << "  After swapping remaining A with C: ans=" << ans << " C=" << C << "\n";

            ans += B;
            B = 0;
            cout << "  After changing B (0->1): ans=" << ans << "\n";

            ans += C + D;
            cout << "  After setting all ?: ans=" << ans << "\n\n";
        }
    }
}
