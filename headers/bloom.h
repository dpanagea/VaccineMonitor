#ifndef BLOOM_H
#define BLOOM_H

#include "functions.h"

typedef struct bloom
{
    void* array;
    unsigned long size;
}bloom;

unsigned long djb2(unsigned char*);
unsigned long sdbm(unsigned char*);
unsigned long hash_i(unsigned char*, unsigned int);

bloom* bloomInit(unsigned long);
void bloomDel(bloom*);
void bloomAdd(bloom*, char*);
int bloomFind(bloom*, char*);


#endif 
