#include <bits/stdc++.h>
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
//
// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode* next) : val(x), next(next) {}
// };
//
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *f, *b;
        f = head;
        b = head;

        for (int i = 0; i < n; i++) {
            f = f->next;
        }
        if (f== nullptr) {
            return b->next;
        }
        f = f->next;
        b = b->next;
        ListNode* p = head;
        while (f != nullptr) {
            f = f->next;
            p = b;
            b = b->next;
        }
        p->next = b->next;
        return head;
    }
};
