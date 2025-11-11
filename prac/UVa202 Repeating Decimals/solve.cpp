#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int dividened;
    int quotient;
    int remainder;
} step;

typedef struct {
    vector<step> steps;
    int divisor;
} question;

void nextStep(question& q) {
    auto last = q.steps.back();
    if (last.remainder == 0) {
        return;
    }
    int new_dividened = last.remainder * 10;
    int new_quotient = new_dividened / q.divisor;
    int new_remainder = new_dividened % q.divisor;
    q.steps.push_back({new_dividened, new_quotient, new_remainder});
}

auto init_question(int dividened, int divisor) {
    int first_dividened = dividened;
    int first_quotient = first_dividened / divisor;
    int first_remainder = first_dividened % divisor;

    step first_step = {first_dividened, first_quotient, first_remainder};
    return question{{first_step}, divisor};
}

void disp_question(const question& q) {
    auto s = q.steps;
    for (auto i : s) {
        cout << i.quotient;
    }
}

int find_repeat(const question& q) {
    if (q.steps.empty())
        return -1;
    if (q.steps.size() <= 1)
        return -1;
    auto last = q.steps.back();
    auto is_equal = [](const step& a, const step& b) {
        return a.dividened == b.remainder;
    };
    for (size_t i = 0; i < q.steps.size(); i++) {
        if (is_equal(q.steps[i], last)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    auto q = init_question(2, 7);
    while (find_repeat(q) == -1) {
        nextStep(q);
    }
    disp_question(q);
    return 0;
}
