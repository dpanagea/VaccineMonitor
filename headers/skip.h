#ifndef SKIP_H
#define SKIP_H

#include "functions.h"

#define MAXSKIP 22 

typedef struct snode
{
    void* value;
    struct snode* next;
    struct snode* down;

}snode;

typedef struct skiplist
{  
    void* levels[MAXSKIP];
}skip;



int randLvl();
skip* skipInit();
snode* snodeInit(void*);
void skipAdd(skip*, void*);
snode* skipFind(skip*, char*);
void skipDel(skip*);
void snodeDel(skip*, void*); /* del snode with certain ID */
void skipPrint(skip*);


#endif

