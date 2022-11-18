#include <stddef.h>
#include <stdio.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if (head == NULL) {
        return 0;
    }
    node *fast_ptr = head;
    node *slow_ptr = head;
    // the fast_ptr->next should not be NULL
    // we need to use it to advance it by two nodes
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
        if (fast_ptr == slow_ptr) {
            return 1;
        }
    }
    return 0;
}
