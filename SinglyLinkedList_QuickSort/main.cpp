#include <cstdio>
#include <iostream>
using namespace std;

/* a node of the singly linked list */
struct Node {
    int data;
    struct Node* next;
};

/* A utility function to insert a node at the beginning of
* linked list */
void push(struct Node** head_ref, int new_data)
{
    /* allocate node */
    struct Node* new_node = new Node;

    /* put in the data */
    //[2] 코드를 작성하세요.
    new_node->data = new_data;

    /* link the old list off the new node */
    //[3] 코드를 작성하세요.
    new_node->next = *head_ref;

    /* move the head to point to the new node */
    //[4] 코드를 작성하세요.
    *head_ref = new_node;
}

/* A utility function to print linked list */
void printList(struct Node* node)
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Returns the last node of the list
struct Node* getTail(struct Node* cur)
{
    // [1] 코드를 작성하세요.
    if (cur == NULL || cur->next == NULL)
    {
        return cur;
    }
    while (cur->next != NULL)
    {
        return getTail(cur->next);
    }
}

// Partitions the list taking the last element as the pivot
struct Node* partition(struct Node* head, struct Node* end,
    struct Node** newHead,
    struct Node** newEnd)
{
    struct Node* pivot = end;
    struct Node* prev = NULL, * cur = head, * tail = pivot;

    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->data < pivot->data) {
            // First node that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;

            //[5] 코드를 작성하세요. --> cur가 tail 이 되면 됩니다.
            tail->next = cur;       // cur가 pivot보다 크면 tail 뒤에 옮겨서 정렬한다
            cur = cur->next;        // 다음 비교를 위해 cur을 다음 리스트를 가리키도록 한다
            tail = tail->next;      // tail 뒤에 pivot보다 큰 리스트가 이동됐으므로 tail을 재설정한다
            tail->next = NULL;      // tail의 next는 null이 되도록 설정한다
        }
    }

    // If the pivot data is the smallest element in the
    // current list, pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;

    // Update newEnd to the current last node
    (*newEnd) = tail;

    // Return the pivot node
    return pivot;
}

// here the sorting happens exclusive of the end node
struct Node* quickSortRecur(struct Node* head,
    struct Node* end)
{
    // base condition
    if (!head || head == end)
        return head;

    Node* newHead = NULL, * newEnd = NULL;

    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    struct Node* pivot
        = partition(head, end, &newHead, &newEnd);

    // If pivot is the smallest element - no need to recur
    // for the left part.
    if (newHead != pivot) {
        // Set the node before the pivot node as NULL
        struct Node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);

        // Change next of last node of the left half to
        // pivot
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// The main function for quick sort. This is a wrapper over
// recursive function quickSortRecur()
void quickSort(struct Node** headRef)
{
    (*headRef)
        = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

// Driver code
int main()
{
    struct Node* a = NULL;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 3);
    push(&a, 30);

    cout << "Linked List before sorting \n";
    printList(a);

    quickSort(&a);

    cout << "Linked List after sorting \n";
    printList(a);

    return 0;
}