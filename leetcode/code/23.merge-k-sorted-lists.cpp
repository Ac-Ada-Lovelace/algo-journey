#include <bits/stdc++.h>
#include <queue>
#include "defs.h"
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNodeCmp {
    bool operator()(const ListNode* a, const ListNode* b) const {
        return a->val > b->val;
    }
};
class Solution {
public:
    void forward(ListNode*& node) {
        node = node->next;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCmp> pq;
        ListNode *head = nullptr, *tail = nullptr;

        for (auto node : lists) {
            if (node) {
                pq.push(node);
            }
        }
        if (pq.empty()) {
            return nullptr;
        }

        head = pq.top();
        tail = head;

        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();

            if (node != head) {
                tail->next = node;
                tail = tail->next;
            }

            forward(node);
            if (node) {
                pq.push(node);
            }
        }

        return head;
    }
};
