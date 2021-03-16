#include "../headers/lists.h"

listnode* nodeInit(void* value)
{
    listnode* new = (listnode*)malloc(sizeof(listnode));
    new->value = value;
    new->next = NULL;
    new->previous = NULL;

    return new;
}

list* listInit()
{
    list* new = (list*)malloc(sizeof(list));
    new->head = NULL;
    new->tail = NULL;
    
    return new;
}

void listAdd(listnode* lnode, list* List) /* adds to the end of the list */
{
    if(List->head == NULL)
    {
        List->head = lnode;
        List->tail = lnode;
    }
    else
    {
        List->tail->next = lnode;
        lnode->previous = List->tail;
        List->tail = lnode;
    }
    List->items++;
}

void listCitPrint(list* List)
{
    listnode* temp = List->head;
    citizen* current;
    while(temp != NULL && temp->value!=NULL)
    {
        current = temp->value;
        printf("%d %s %s %d %s -> \n", current->id, current->firstname, current->lastname, current->age, current->country);
        printf("Total items in list: %d \n", List->items);
        temp = temp->next;
    }
}

// void nodeDel(lnode, )
