#include <bits/stdc++.h>
using namespace std;

struct Node {
  int id;
  Node *prev;
  Node *next;
};

Node* buildCircle(int n) {
  Node* head = new Node{1, nullptr, nullptr};
  Node* prev = head;
  for (int i = 2; i <= n; ++i) {
    Node* cur = new Node{i, prev, nullptr};
    prev->next = cur;
    prev = cur;
  }
  head->prev = prev;
  prev->next = head;
  return head;
}

Node* advanceClockwise(Node* node, int steps) {
  while (--steps) node = node->next;
  return node;
}

Node* advanceCounter(Node* node, int steps) {
  while (--steps) node = node->prev;
  return node;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k, m;
  while (cin >> n >> k >> m) {
    if (!n && !k && !m) break;
    Node* head = buildCircle(n);
    Node* a = head;
    Node* b = head->prev;
    int remaining = n;
    bool first = true;

    while (remaining > 0) {
      a = advanceClockwise(a, k);
      b = advanceCounter(b, m);

      if (!first) cout << ",";
      first = false;

      if (a == b) {
        cout << setw(3) << a->id;
        if (a->next == a) {
          delete a;
          a = b = nullptr;
          --remaining;
          break;
        }
        Node* next = a->next;
        Node* prev = a->prev;
        a->prev->next = a->next;
        a->next->prev = a->prev;
        delete a;
        a = next;
        b = prev;
        --remaining;
      } else {
        cout << setw(3) << a->id << setw(3) << b->id;
        Node* nextA = (a->next == b) ? b->next : a->next;
        Node* prevB = (b->prev == a) ? a->prev : b->prev;

        a->prev->next = a->next;
        a->next->prev = a->prev;
        b->prev->next = b->next;
        b->next->prev = b->prev;
        delete a;
        delete b;
        a = nextA;
        b = prevB;
        remaining -= 2;
      }
    }
    cout << "\n";
  }

  return 0;
}
