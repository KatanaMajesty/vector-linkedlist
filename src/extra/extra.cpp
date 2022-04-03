#include <stdlib.h>

// C++
class ListNode
{
public:
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverse(ListNode* head)
{
    ListNode* p = head;
    ListNode* prev = NULL;
    ListNode* curr = NULL;
    while (p != NULL)
    {
        curr = p;
        p = p->next;
        curr->next = prev;
        prev = curr;
    }
    return (head = curr);
}

int hasCycle(ListNode *head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) 
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) 
            return 1;
    }     
    return 0;
}