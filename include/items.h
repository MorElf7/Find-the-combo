#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>

struct Item {
    char* name;
    struct Item* next;
};

//function to add in front of a linked list
int add_item(struct Item** head, char* target);

//function to remove a specified node from linked list
int drop_item(struct Item** head, char* target);

//function to check if a linked list has a specified data
int include(struct Item* head, char* target);

//function to print all the node of the linked list
void list(struct Item* head);

#endif