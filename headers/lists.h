#ifndef _LISTS_
#define _LISTS_ 

#include "functions.h"



typedef struct listnode
{
    citizen value;
    struct listnode* previous;
    struct listnode* next;    
}listnode;  


#endif
