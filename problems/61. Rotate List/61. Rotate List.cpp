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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return nullptr;
        ListNode* tmp = head;
        int len = 0;
        while(tmp != nullptr) {
            len++;
            tmp = tmp -> next;
        }
        tmp = head;

        for(int i = 0; i < (k%len); i++) {
            ListNode* lastNode = head;
            tmp = head;
            while(tmp->next != nullptr){
                lastNode = tmp;
               tmp = tmp->next;
            }
            lastNode->next = nullptr;
            tmp->next = head;
            head = tmp;
        }
    return head;
    }
};