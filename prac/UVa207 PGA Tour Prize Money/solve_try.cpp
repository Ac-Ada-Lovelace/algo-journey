#include <bits/stdc++.h>

using namespace std;

typedef struct {
    string name;
    array<int, 4> rounds;
    int total;
    bool has_dq;
    int effective_rounds;
} player;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}
struct player_cmp {
    bool operator()(const player& a, const player& b) const {
        if (a.has_dq && b.has_dq) {
            if (a.total != b.total) {
                return a.total < b.total;
            } else if (a.effective_rounds != b.effective_rounds) {
                return a.effective_rounds < b.effective_rounds;
            }
            return a.name > b.name;
        }
        if (a.has_dq) {
            return true;
        }
        if (b.has_dq) {
            return false;
        }
        if (a.total != b.total) {
            return a.total < b.total;
        }
        return a.name > b.name;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) {
        string s;
        getline(cin, s);
        double total_prize;
        cin >> total_prize;
        array<double, 71> prize_by_rank;
        for (int i = 1; i <= 70; i++) {
            double percentage;
            cin >> percentage;
            prize_by_rank[i] = total_prize * percentage / 100.0;
        }

        int player_num;

        cin >> player_num;
        priority_queue<player, vector<player>, player_cmp> players;
        while (player_num--) {
            string line;
            getline(cin, line);
            vector<string> parts = split(line, ' ');
            player p{"", {0, 0, 0, 0}, 0, 0};
            int total = 0;
            for (int i = 4; i >= 0; i--) {
                auto score = parts.back();
                parts.pop_back();
                if (score == "DQ") {
                    p.rounds[i] = -1;
                    p.has_dq = true;
                } else {
                    int score_value = stoi(score);
                    p.rounds[i] = score_value;
                    total += score_value;
                    p.effective_rounds++;
                }
            }
            p.total = total;
            string name = "";
            for (auto p : parts) {
                name += p;
            }

            players.push(p);
        }
    }
}
