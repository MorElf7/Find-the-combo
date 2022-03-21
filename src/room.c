#include "room.h"
#include "items.h"
#include <string.h>
#include <stdlib.h>

int characterLocation[MAX_CHARACTER], availItem[MAX_ITEM];
char* answer[3];

void initRooms(struct Room** grid) {
    struct Room* board = *grid;
    struct Room* cur;
    
    srand(time(NULL));

    itemCount = (rand() % (MAX_ITEM - MIN_ITEM + 1)) + MIN_ITEM;
    characterCount = (rand() % (MAX_CHARACTER - MIN_CHARACTER + 1)) + MIN_CHARACTER;

    int rooms[9] = {0};

    for (int i = 0; i < 9; i++) {
        characterLocation[i] = -1;
        availItem[i] = 0;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cur = board + 3 * i + j;
            int n = rand() % 9;
            if (rooms[n] != 0) {
                while (rooms[n] != 0) n = rand() % 9;
            }
            rooms[n]++;
            cur->name = strdup(roomName[n]);
            cur->characterNumber = 0;
            for (int i = 0; i < 9; i++) {
                cur->character[i] = NULL;
            }
            cur->itemList = NULL;

            int l = j - 1, r = j + 1;
            int u = i - 1, d = i + 1;

            if (l < 0) {
                cur->West = NULL;
            } else {
                cur->West = board + 3*i + l;
            }
            if (r >= 3) {
                cur->East = NULL;
            } else {
                cur->East = board + 3*i + r;
            }
            if (u < 0) {
                cur->North = NULL;
            } else {
                cur->North = board + 3*u + j;
            }
            if (d >= 3) {
                cur->South = NULL;
            } else {
                cur->South = board + 3*d + j;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        rooms[i] = 0;
    }

    answer[0] = roomName[rand() % 9];
    int i = 0;
    while (i < itemCount) {
        int n = rand() % MAX_ITEM, m = rand() % 9;
        if (availItem[n] == 0 && rooms[m] == 0) {
            cur = board + m;
            add_item(&(cur->itemList), itemName[n]);
            availItem[n]++;
            answer[1] = itemName[n];
            rooms[m]++;
            i++;
        } else continue;
    }

    for (int i = 0; i < 9; i++) {
        rooms[i] = 0;
    }
    i = 0;

    while (i < characterCount) {
        int n = rand() % MAX_CHARACTER, m = rand() % 9;
        if (characterLocation[n] < 0 && rooms[m] == 0) {
            cur = board + m;
            cur->character[0] = characterName[n];
            characterLocation[n] = m;
            cur->characterNumber++;
            answer[2] = characterName[n];
            rooms[m]++;
            i++;
        } else continue;
    }
    
    return;
}

void move(struct Room** board, int * avatar, char* direction) {
    struct Room* pos = (*board) + *avatar;
    if (direction == NULL) {
        printf("Invalid action!\n");
        return;
    }
    if (strcmp(direction, "north") == 0) {
        if (pos->North == NULL) {
            printf("There is nothing North!\n");
            return;
        }
        *avatar -= 3;
    } else if (strcmp(direction, "east") == 0) {
        if (pos->East == NULL) {
            printf("There is nothing East!\n");
            return;
        }
        *avatar += 1;
    } else if (strcmp(direction, "south") == 0) {
        if (pos->South == NULL) {
            printf("There is nothing South!\n");
            return;
        }
        *avatar += 3;
    } else if (strcmp(direction, "west") == 0) {
        if (pos->West == NULL) {
            printf("There is nothing West!\n");
            return;
        }
        *avatar -= 1;
    } else {
        printf("Invalid direction!\n");
        return;
    }
    printf("You are now in the %s.\n", ((*board) + *avatar)->name);
    return;
}

void look(struct Room* pos) {
    printf("You are now in the %s.\n", pos->name);
    if (pos->North != NULL) printf("North of you is the %s.\n", pos->North->name);
    if (pos->South != NULL) printf("South of you is the %s.\n", pos->South->name);
    if (pos->East != NULL) printf("East of you is the %s.\n", pos->East->name);
    if (pos->West != NULL) printf("West of you is the %s.\n", pos->West->name);
    printf("These items are in the room.\n");
    list(pos->itemList);
    printf("These characters are in the room.\n");
    for (int i = 0; i < pos->characterNumber; i++) {
        printf("%s  ", pos->character[i]);
    }
    return;
}

int removeElementArray(char* arr[], char* target, int n) {
    int i = 0;
    while (i < n && strcmp(target, arr[i]) != 0) i++;
    if (i >= n) return 0;
    for (int j = i; j < n - 1; j++) {
        arr[j] = arr[j+1];
    }
    arr[n - 1] = NULL;
    return 1;
}

int clue(int pos, struct Room** board, char* target) {
    if (target == NULL) return 0;
    int n = 0;
    while (n < MAX_CHARACTER && strcmp(target, characterName[n]) != 0) n++;
    if (n >= MAX_CHARACTER) return 0;
    struct Room* temp = (*board) + characterLocation[n];
    int len = sizeof(temp->character) / sizeof(temp->character[0]);
    int check = removeElementArray(temp->character, target, len);
    if (check) {
        temp->characterNumber--;
        temp = *board + pos;
        temp->character[temp->characterNumber] = target;
        temp->characterNumber++;
        characterLocation[n] = pos;
    } else return 0;
    return 1;
}