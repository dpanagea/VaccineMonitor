#include "../headers/skip.h"
#include <stdio.h>
#include <stdlib.h>
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
    record *temp, *rec;
    citizen *tcit, *rcit;
    rec = (struct record*)value;
    up = NULL;
    int i, lvl;
    lvl = randLvl();
    for(i = lvl-1; i>=0; i--)
    {
        curr = slist->levels[i];
        while(curr->next != NULL)
        {
            temp = curr->next->value;
            tcit = temp->person->value;
            rcit = rec->person->value;
            if(atoi(tcit->id) > atoi(rcit->id)) 
                break;
            curr = curr->next;
        }
        new = snodeInit(rec);
        new->next = curr->next;
        curr->next = new;
        if (up != NULL)
            up->down = new;
        up = new;
    }
}

void snodeDel(skip* slist, void* value)
{
    snode *curr, *del, *scit;
    record *rtemp, *rcit;
    citizen *temp, *cit;

    scit = value;
    rcit = (struct record*)scit->value;
    cit = rcit->person->value;
    int i;
    for(i = MAXSKIP-1; i>=0; i--)
    {
        curr = slist->levels[i];
        while(curr->next != NULL)
        {
            rtemp = curr->next->value;
            temp = rtemp->person->value;
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

void skipPrint(skip* slist)
{
    snode *curr;
    record *rcit;
    citizen *cit;
    int i;
    for(i=MAXSKIP-1; i>=0; i--)
    {
        curr = slist->levels[i];
        if(curr->next != NULL)
        {
            while(curr->next != NULL)
            {
                curr = curr->next;
                rcit = (record*)curr->value;
                cit = rcit->person->value;
                printf("%s->", cit->id);
            }
            printf("\n");
        }
    }
}

snode* skipFind(skip* slist, char* value)
{
    int flag = 0;
    if(slist != NULL)
    {
        
        snode *curr; 
        citizen *temp;
        record *rtemp;
    //    int i = 0;
        int currid, findid;
        findid = atoi(value);
        curr = slist->levels[0];
        curr = curr->next;
        while(!flag && curr!= NULL)
        {
            rtemp = (record*)curr->value;
            temp = (citizen*)rtemp->person->value;
            currid = atoi(temp->id);
            if(findid == currid)
                flag = 1;
            else 
                curr = curr->next; 
        }
        /*
        for(i = MAXSKIP-1; i>=0 && !flag; i--)
        {
            curr = slist->levels[0];
            while(!flag && curr->next != NULL)
            {
                rtemp = (record*)curr->next->value;
                temp = (citizen*)rtemp->person->value;
                currid = atoi(temp->id);    
                if(currid == findid) 
                {
                    flag = 1;
                }
                else if(currid > findid && curr->value != NULL)
                    curr = curr->down;
                else 
                    curr = curr->next;
                if(!flag && curr == NULL)  // that means that curr is at setinel 
                    curr->next = NULL;
            }
               
        }*/

        if(flag == 0){return NULL;}
        else {return curr;}
    }
    else
    {
        printf("Error. NULL skip list.\n");
        return NULL;
    }
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


