#include "items.h"
#include <string.h>
#include <stdlib.h>

int add_item(struct Item** head, char* target) {
    if (target == NULL) return 0;
    struct Item* item = (struct Item*)malloc(sizeof(struct Item));
    item->name = strdup(target);
    item->next = *head;
    (*head) = item;
    return 1;
}

int drop_item(struct Item** head, char* target) {
    struct Item* cur = *head, *prev = NULL;
    if (strcmp((*head)->name, target) == 0) {
        (*head) = (*head)->next;
        free(cur->name);
        free(cur);
        return 1;
    }
    
    while (cur != NULL && strcmp(target, cur->name) != 0) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return 0;
    prev->next = cur->next;
    
    free(cur->name);
    free(cur);
    return 1;
}

int include(struct Item* head, char* target) {
    struct Item* cur = head;
    while (cur != NULL && strcmp(target, cur->name) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) return 0;
    else return 1;
}

void list(struct Item* head) {
    struct Item* cur = head;
    if (head == NULL) {
        printf("There is nothing.\n");
        return;
    }
    while (cur != NULL) {
        printf("%s  ", cur->name);
        cur = cur->next;
    }
    printf("\n");
    return;
}
