#include <bits/stdc++.h>
using namespace std;

struct lkn {
    lkn* nxt;
    lkn* prv;
    int key;
    int val;
};

struct lnk {
public:
    lkn* head;
    lkn* tail;
    int capcacity;
    int size;

    unordered_map<int, lkn*> mp;

    void remove_by_key(int key) {
        auto it = mp.find(key);
        if (it == mp.end())
            return;
        lkn* node = it->second;
        if (node->prv) {
            node->prv->nxt = node->nxt;
        } else {
            head = node->nxt;
        }
        if (node->nxt) {
            node->nxt->prv = node->prv;
        } else {
            tail = node->prv;
        }
        mp.erase(it);
        delete node;
        size--;
    }

    int get_by_key(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }
        lkn* node = mp[key];
        if (node != head) {
            // remove node from its current position
            if (node->prv) {
                node->prv->nxt = node->nxt;
            }
            if (node->nxt) {
                node->nxt->prv = node->prv;
            } else {
                tail = node->prv;
            }
            // insert node at head
            node->nxt = head;
            node->prv = nullptr;
            if (head) {
                head->prv = node;
            }
            head = node;
            if (!tail) {
                tail = head;
            }
        }
        return node->val;
    }

    int put_by_key(int key, int value) {
        if (mp.find(key) != mp.end()) {
            remove_by_key(key);
        }
        if (size == capcacity) {
            // remove tail
            if (tail) {
                remove_by_key(tail->key);
            }
        }
        lkn* node = new lkn();
        node->key = key;
        node->val = value;
        node->nxt = head;
        node->prv = nullptr;
        if (head) {
            head->prv = node;
        }
        head = node;
        if (!tail) {
            tail = head;
        }
        mp[key] = node;
        size++;
        return 0;
    }
};

class LRUCache {
public:
    lnk cache;
    LRUCache(int capacity) {
        cache = lnk();
        cache.capcacity = capacity;
        cache.size = 0;
        cache.head = nullptr;
        cache.tail = nullptr;
    }

    int get(int key) {
        return cache.get_by_key(key);
    }

    void put(int key, int value) {
        cache.put_by_key(key, value);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
