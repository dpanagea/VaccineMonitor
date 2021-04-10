#include "../headers/skip.h"
#include <time.h>

int randLvl() /* random num between [1,MAXSKIP-1] for levels of each num */
{
    int temp = 1;
    while((float) rand()/(float) RAND_MAX > 0.5 && temp < MAXSKIP)
        temp++;

    return temp;
}

skip* skipInit()
{
    skip* new = (skip*)malloc(sizeof(skip));
    int i;
    for(i = 0; i < MAXSKIP; i++)
        new->levels[i] = snodeInit(NULL);
    return new;
}

snode* snodeInit(void* value)
{
    snode* new = (snode*) malloc(sizeof(snode));
    new->value = value;
    new->next = NULL;
    new->down = NULL;
    return new;
}

void skipAdd(skip* slist, void* value)
{
    snode *curr, *up, *new;
    citizen *temp, *cit;
    cit = (struct citizen*)value;
    up = NULL;
    int i, lvl;
    lvl = randLvl();
    for(i = lvl-1; i>=0; i--)
    {
        curr = slist->levels[i];
        while(curr->next != NULL)
        {
            temp = curr->next->value;
            if(atoi(temp->id) > atoi(cit->id)) 
                break;
            curr = curr->next;
        }
        new = snodeInit(cit);
        new->next = curr->next;
        curr->next = new;
        if (up != NULL)
            up->down = new;
        up = new;
    }
}

void snodeDel(skip* slist, void* value)
{
    snode *curr, *del;
    citizen *temp, *cit;
    cit = (struct citizen*)value;
    int i;
    for(i = MAXSKIP-1; i>=0; i--)
    {
        curr = slist->levels[i];
        while(curr->next != NULL)
        {
            temp = curr->next->value;
            if(atoi(temp->id) > atoi(cit->id))
                break;
            curr = curr->next;
        }
        if(curr != NULL)
        {
            del = curr->next;
            curr->next = del->next;
            free(del);
        }
    }

}

snode* skipFind(skip* slist, void* value)
{
    snode *curr; 
    citizen *temp, *cit;
    cit = (struct citizen*)value;
    int i, flag = 0;
    for(i = MAXSKIP-1; i>=0; i--)
    {
        curr = slist->levels[i];
        while(!flag && curr->next != NULL)
        {
            temp = curr->next->value;
            if(atoi(temp->id) == atoi(cit->id)) /* found */
                flag = 1;
            else if(atoi(temp->id) > atoi(cit->id))
                curr = curr->down;
            else 
                curr = curr->next;
            if(curr->value == NULL)  /*that means that curr is at setinel */
                curr->next = NULL;
        }
    }
    return curr->next;
}

void skipDel(skip* slist)
{
    int i;
    snode *curr, *temp;
    for (i = MAXSKIP - 1; i >= 0; i--)
    {
        curr = slist->levels[i];
        while(curr != NULL)
        {
            temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(curr);
    }
    free(slist);
}
