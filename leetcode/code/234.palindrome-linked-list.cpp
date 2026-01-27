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
    ListNode* front;
    bool recursivelyCheck(ListNode* current) {
        if (current != nullptr) {
            if (!recursivelyCheck(current)) {
                return false;
            }
            if (current->val != front->val) {
                return false;
            }
            front = front->next;
        }
        return true;
    }
    bool isPalindrome(ListNode* head) {
        front = head;
        return recursivelyCheck(head);
    }
};
