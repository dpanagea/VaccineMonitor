#include "../headers/lists.h"

listnode* nodeInit(void* value)
{
    listnode* new = (listnode*)malloc(sizeof(listnode));
    new->value = value;
    new->next = NULL;
    new->previous = NULL;

    return new;
}

list* listInit(listnode* lnode)
{
    list* new = (list*)malloc(sizeof(list));
    new->head = lnode;
    new->tail = lnode;
    new->items++;
    
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

void listPrint(list* List)
{
    listnode* temp = List->head;
    citizen* current;
    while(temp != NULL && temp->value!=NULL)
    {
        current = temp->value;
        printf("ID: %d | First name: %s | Last name: %s | Age: %d | Country: %s ", current->id, current->firstname, current->lastname, current->age, current->country);

        temp = temp->next;
    }

}
