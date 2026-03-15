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
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carryIn = 0;
        ListNode* newListHead = new ListNode();
        ListNode* start = newListHead;
        while(l1 != nullptr && l2 != nullptr){
            int res = l1->val + l2->val + carryIn;
            carryIn = res / 10;
            ListNode* node = new ListNode(res%10);
            if (newListHead->next == nullptr) {
                newListHead->next = node;
                start = start -> next;
            } else {
                start->next = node;
                start = start->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode* remainPart = l1 == nullptr ? l2 : l1;
        while(remainPart != nullptr) {
            int res = remainPart->val + carryIn;
            carryIn = res / 10;
            ListNode* node = new ListNode(res%10);
            if (newListHead->next == nullptr) {
                newListHead->next = node;
                start = start -> next;
            } else {
                start->next = node;
                start = start->next;
            }
            remainPart = remainPart->next;
        }
        if (carryIn) {
            ListNode* lastEl = new ListNode(1);
            start->next = lastEl;
        }
        return newListHead->next;
    }
};