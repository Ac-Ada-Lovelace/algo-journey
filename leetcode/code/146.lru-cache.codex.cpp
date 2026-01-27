#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
  struct Node {
    int key;
    int val;
    Node* prev;
    Node* next;
  };

  int capacity_;
  unordered_map<int, Node*> mp_;
  Node* head_;
  Node* tail_;

  void add_front(Node* node) {
    node->next = head_->next;
    node->prev = head_;
    head_->next->prev = node;
    head_->next = node;
  }

  void remove_node(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void move_to_front(Node* node) {
    remove_node(node);
    add_front(node);
  }

  Node* pop_tail() {
    Node* node = tail_->prev;
    remove_node(node);
    return node;
  }

public:
  LRUCache(int capacity) : capacity_(capacity) {
    head_ = new Node{0, 0, nullptr, nullptr};
    tail_ = new Node{0, 0, nullptr, nullptr};
    head_->next = tail_;
    tail_->prev = head_;
  }

  ~LRUCache() {
    for (auto& kv : mp_) {
      delete kv.second;
    }
    delete head_;
    delete tail_;
  }

  int get(int key) {
    auto it = mp_.find(key);
    if (it == mp_.end()) return -1;
    Node* node = it->second;
    move_to_front(node);
    return node->val;
  }

  void put(int key, int value) {
    auto it = mp_.find(key);
    if (it != mp_.end()) {
      Node* node = it->second;
      node->val = value;
      move_to_front(node);
      return;
    }

    if (capacity_ == 0) return;

    if ((int)mp_.size() == capacity_) {
      Node* node = pop_tail();
      mp_.erase(node->key);
      delete node;
    }

    Node* node = new Node{key, value, nullptr, nullptr};
    add_front(node);
    mp_[key] = node;
  }
};

