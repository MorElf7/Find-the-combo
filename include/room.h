#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CHARACTER 8
#define MIN_CHARACTER 5
#define MAX_ITEM 9
#define MIN_ITEM 6

//room, item, and character name to choose from to create the game
static char* characterName[MAX_CHARACTER] = {"Alpha", "Beta", "Charlie", "Delta", "Echo", "Falcon", "Omega", "Zeta"};
static char* itemName[MAX_ITEM] = {"CPU", "GPU", "RAM", "HDD", "SSD", "KEYBOARD", "WEBCAM", "MONITOR", "MOUSE"};
static char* roomName[9] = {"Kitchen", "Bathroom", "Master Bedroom", "Guest Bedroom", "Living Room", "Game Room", "Ball Room", "Garden", "Basement"};

//the number of item and character that exist in a single game, create with rand() in room.c
// 6 <= itemCount <= 9, 5 <= characterCount <= 8
static int itemCount, characterCount;

//array to track the location of every character as well as the existent of each item
extern int characterLocation[MAX_CHARACTER], availItem[MAX_ITEM];

//array to store the answer
extern char* answer[3];//room, item, character

struct Room {
    char *name;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* itemList;
    int characterNumber;
    char* character[MAX_CHARACTER];
};

//function to create the setting
void initRooms(struct Room** grid);

//function to let the avatar move
void move(struct Room** board, int* avatar, char* direction);

//function to display what is in the room
void look(struct Room* pos);

//function to bring the mention character to where the avatar is
int clue(int pos, struct Room** board, char* target);

#endif