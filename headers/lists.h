#ifndef _LISTS_
#define _LISTS_ 

#include "functions.h"

typedef struct listnode
{
    void* value;                /* we have different lists, no point in creating diff structs */
    struct listnode* previous;
    struct listnode* next;    
}listnode;  

typedef struct list
{
    int items;              /* Holds the num of items currently stored in the list */
    struct listnode* head;
    struct listnode* tail;
}list;

listnode* nodeInit(void*);
list* listInit();
void listAdd(listnode*, list*);
void listCitPrint(list*);

void listDel(list*);


int virusInList(char*, list*);                   /* check if virus already in list */
struct record* recInList(int, list*, listnode*); /* check if record with citizen ID exists in list,
                                                    starting from a certain node. Return the first found.
                                                    No need to check in citizens' list, if there is a rec with
                                                    same ID, then the citizen is already in the list */

#endif
