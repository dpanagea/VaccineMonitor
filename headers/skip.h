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
void skipAdd(skip*, citizen*);
snode* skipFind(skip*, citizen*);
void skipDel(skip*);
void snodeDel(skip*, citizen*); /* del snode with certain ID */

#endif

