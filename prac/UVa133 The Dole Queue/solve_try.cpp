#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    Node* left;
    Node* right;
};

Node* create_circle(int N) {
    Node* head = new Node{1, nullptr, nullptr};
    Node* prev = head;
    for (int i = 2; i <= N; i++) {
        Node* new_node = new Node{i, nullptr, nullptr};
        prev->right = new_node;
        new_node->left = prev;
        prev = new_node;
    }
    prev->right = head;
    head->left = prev;
    return head;
}

Node* remove_node(Node* node) {
    node->left->right = node->right;
    node->right->left = node->left;
    Node* next_node = node->right;
    delete node;
    return next_node;
}

void walk_clockwise(Node*& start, int k) {
    for (int i = 1; i < k; i++) {
        start = start->right;
    }
}
void walk_counterclockwise(Node*& start, int m) {
    for (int i = 1; i < m; i++) {
        start = start->left;
    }
}
void output_candidate(int i, int& N) {
    cout << left << setw(3) << i;
    if (N == 1)
        cout << ",";
    N--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, k, m;
    while (cin >> N >> k >> m) {
        if (N == 0 && k == 0 && m == 0) {
            break;
        }
        auto candidates = create_circle(N);
        auto officer_A = candidates;
        auto officer_B = candidates->left;

        while (N > 0) {
            walk_counterclockwise(officer_A, k);
            walk_clockwise(officer_B, m);

            int flag = (officer_A == officer_B);
            walk_counterclockwise(officer_A, 1);
            walk_clockwise(officer_B, 1);

            if (flag) {
                output_candidate(officer_A->right->id, N);
                remove_node(officer_A->right);
            }

            output_candidate(officer_A->right->id, N);
            remove_node(officer_A->right);

            output_candidate(officer_B->left->id, N);
            remove_node(officer_B->left);
        }
    }
}
