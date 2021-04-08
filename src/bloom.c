#include "../headers/bloom.h"

unsigned long djb2(unsigned char* str)
{
    usnigned long hash = 5381;
    int c;
    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ 
    }
    return hash;
}

unsigned long sdbm(unsigned char* str)
{
    unsigned long hash = 0;
    int c;
    while (c = *str++)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

unsigned long hash_i(unsigned char* str, unsigned int i)
{
    return djb2(str) + i*sdbm(str) + i*i;
}

bloom* bloomInit(unsigned long bsize)
{
    bloom* curr = (bloom*)malloc(sizeof(bloom));
    curr->size = bsize; /* bsize is in bytes  */ 
    curr->array = malloc(curr->size);
    int i;
    for(i = 0; i < curr->size; i++)
    {
        curr->array[i] = 0;     /* set each byte to 0 - so each bit to 0 */
    }

    return curr;
}

void bloomDel(bloom* bf)
{
    free(bf->array);
    free(bf);
}

void bloomAdd(bloom* bf, record* rec)
{
    int i;
    citizen* cit = rec->person->value;
    char id[5]; /* id is max 4 digits */
    itoa(cit->id, id, 10);
    unsigned long pos; 
    for (i = 0; i < MAXK; i++)
    {
        pos = hash_i(id, i) % (bf->size*8); /*the desired pos should be of the bit */
        bf->array[pos/8] |= 1 (pos % 8);    /* set the pos bit to 1 */
    }
}

int bloomFind(bloom* bf, record* rec)
{
    int i; 
    citizen* cit = rec->person->value;
    char id[5];
    itoa(cit->id, id, 10);
    unsigned long pos;
    for ( i = 0; i < MAXK; i++)
    {
        pos = hash_i(id, i) % (bf->size*8);
        if (!(bf->[pos/8] & 1 << hash % 8))
            return 0;
        return 1;
    }
}