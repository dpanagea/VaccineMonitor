#include "../headers/bloom.h"
#include <stdint.h>

unsigned long djb2(unsigned char* str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */ 
    }
    return hash;
}

unsigned long sdbm(unsigned char* str)
{
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
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
    curr->array = (char*)malloc(curr->size);
    char* arr = curr->array;
    unsigned long i;
    for(i = 0; i < curr->size; i++)
    {
        arr[i] = 0;     /* set each byte to 0 - so each bit to 0 */
    }

    return curr;
}

void bloomDel(bloom* bf)
{
    free(bf->array);
    free(bf);
}

void bloomAdd(bloom* bf, char* recID)
{
    int i;
    uint8_t* arr = bf->array;
    unsigned long pos; 
    for (i = 0; i < MAXK; i++)
    {
        pos = hash_i((unsigned char*)recID, i) % (bf->size*8); /*the desired pos should be of the bit */
        arr[pos/8] |= 1 << pos % 8;    /* set the pos bit to 1 */
        
    }
}

int bloomFind(bloom* bf, char* recID)
{
    int i; 
    uint8_t* arr = bf->array;
    unsigned long pos;
    int flag = 1;
    
    for ( i = 0; i < MAXK && flag; i++)
    {
        pos = hash_i((unsigned char*)recID, i) % (bf->size*8);
        if (!(arr[pos/8] & 1 << pos % 8))
        {
            flag = 0;
            
        }
    }
    return flag;
}
