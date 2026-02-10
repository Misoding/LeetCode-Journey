/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* firstPointer = head;
        ListNode* secondPointer = head;
        while (head != nullptr && secondPointer != nullptr && secondPointer->next != nullptr) {
            firstPointer = firstPointer->next;
            secondPointer=secondPointer->next->next;
            if (firstPointer == secondPointer) {
                return true;
            }
        }
        return false;
    }
};