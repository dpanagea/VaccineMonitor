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
listnode* listAdd(listnode*, list*);
void listPrint(list*, int); /* depending on int, we have to print a diff type of list. 
                        0 -> virus list
                        1 -> country list
                        2 -> citizen list
                        3 -> record list
                        */
void listDel(list*, int); /* Same as listPrint */


struct listnode* virusInList(char*, list*);                   /* check if virus already in list */
struct listnode* countryInList(char*, list*);                  /* check if country already in list */ 
struct record* recInList(int, list*);             /* check if record with citizen ID exists in list. 
                                                    Return the first found.
                                                    No need to check in citizens' list, if there is a rec with
                                                    same ID, then the citizen is already in the list */
void listDel(list *List, int);

#endif
