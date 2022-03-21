#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "room.h"

int characterLocation[MAX_CHARACTER], availItem[MAX_ITEM];
char* answer[3];

//function to display all the command
void help();

//function to display all the existing rooms, items, and characters
void listAll();

//function to check if there is any match when clue command is called
int checkMatch(struct Room * pos, struct Item * inventory);

//function to process user input
void processCommand(char* command[], char* input);

int main() {
    struct Item* inventory = NULL;
    struct Room* board = (struct Room*)malloc(sizeof(struct Room) * 9);
    initRooms(&board);
    int avatar = 0;
    int clueTries = 10;
    
    char *input;

    while (clueTries > 0) {
        size_t sz = 0;
        int characters;

        printf("----------------------------------------------------------------\n");
        printf("Please type a command: ");
        characters = getline(&input, &sz, stdin);
        char* command[2];
        
        char* in = strdup(input);
        processCommand(command, in);
        

        if (strcmp(command[0], "help") == 0) {
            help();
        } 
        else if (strcmp(command[0], "list") == 0) {
            listAll();
        } 
        else if (strcmp(command[0], "look") == 0) {
            look((board + avatar));
        } 
        else if (strcmp(command[0], "take") == 0) {
            if (include((board + avatar)->itemList, command[1])) {
                int a = add_item(&inventory, command[1]), b = drop_item(&((board + avatar)->itemList), command[1]);
                if(!a || !b) {
                    printf("Invalid action!\n");
                    continue;
                } else {
                    printf("You have picked up %s\n", command[1]);
                }

            } else printf("Invalid action!\n");
        } 
        else if (strcmp(command[0], "drop") == 0) {
            if (include(inventory, command[1])) {
                
                int a = add_item(&((board + avatar)->itemList), command[1]), b = drop_item(&inventory, command[1]);
                if(!(a && b)) {
                    printf("Invalid action!\n");
                    continue;
                } else {
                    printf("You have dropped %s\n", command[1]);
                }

            } else printf("Invalid action!\n");
        } 
        else if (strcmp(command[0], "inventory") == 0) {
            list(inventory);
        } 
        else if (strcmp(command[0], "clue") == 0) {
            int a = clue(avatar, &board, command[1]);
            if (a) {
                clueTries--;
                int x = checkMatch((board + avatar), inventory);
                if (x == 3) {
                    printf("You have chosen all 3 correct answer. You won.\n");
                    return 1;
                } else {
                    printf("Unlucky. You still have %d tries left.\n", clueTries);
                }
            } else printf("Invalid action!\n");
            
        }
        else if (strcmp(command[0], "go") == 0) {
            move(&board, &avatar, command[1]);
        }
        printf("\n"); 
        free(in);
        
    }
    
    if (clueTries == 0) {
        printf("You have run out of tries. Game Over!\n");
    }

    free(input);
    struct Room* temp;
    struct Item* t, *prev;
    for (int i = 0; i < 9; i++) {
        temp = board + i;
        t = temp->itemList;
        prev = t;
        while (t != NULL) {
            prev = t;
            t = t->next;
            free(prev->name);
            free(prev);
        }
    }
    t = inventory;
    while (t != NULL) { 
        prev = t;
        t = t->next;
        free(prev->name);
        free(prev);
    }

    free(board);

    return 1;
}

int checkMatch(struct Room * pos, struct Item * inventory) {
    int count = 0;
    if (strcmp(pos->name, answer[0]) == 0) {
        printf("Room Match\n");
        count++;
    }
    for (int i = 0; i < pos->characterNumber; i++) {
        if (strcmp(pos->character[i], answer[2]) == 0) {
            printf("Character Match\n");
            count++;
        }
    }
    if (include(inventory, answer[1]) || include(pos->itemList, answer[1])) {
        printf("Item Match\n");
        count++;
    }
    return count;
}

void listAll() {
    printf("List of rooms\n");
    for (int i = 0; i < 9; i++) {
        printf("%s  ", roomName[i]);
    }
    printf("\nList of items\n");
    for (int i = 0; i < MAX_ITEM; i++) {
        if (availItem[i] != 0) printf("%s  ", itemName[i]);
    }
    printf("\nList of characters\n");
    for (int i = 0; i < MAX_CHARACTER; i++) {
        if (characterLocation[i] >= 0) printf("%s  ", characterName[i]);
    }
    printf("\n");
    return;
}

void help() {
    printf("Your objective is to bring the correct item and character to the correct room. You have 10 tries\n");
    printf("list                    list available items, rooms, characters\n");
    printf("look                    see where you are and what are around you\n");
    printf("go [direction]          move to another room with 4 direction: north, south, east, west\n");
    printf("take [name]             pick up an item in the room\n");
    printf("drop [name]             drop an item from your inventory\n");
    printf("inventory               check your inventory\n");
    printf("clue [character]        bring the mention character to where you are and check for corerct item, room, and character\n");
    return;
}

void processCommand(char* command[], char* input) {
    int n = strlen(input);
    input[n - 1] = '\0';
    command[0] = strtok(input, " ");
    command[1] = strtok(NULL, " ");
    return;
}