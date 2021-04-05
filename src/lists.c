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

listnode* listAdd(listnode* lnode, list* List) /* adds to the end of the list */
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
    return List->tail;
    
}

void listPrint(list* List, int type)
{
    listnode *temp = List->head;

    if(type == 2)
    {
        citizen *curr;
        country *cntr;
        while(temp != NULL && temp->value != NULL)
        {
            curr = temp->value;
            cntr = curr->origin->value;
            printf("%d %s %s %s %d \n", curr->id, curr->firstname, curr->lastname, cntr->value, curr->age);
            temp = temp->next;
        }
    }
    else if(type == 3)
    {
        record *curr; 
        citizen *cit;
        virus *vir;
        country *cntr;
        while( temp != NULL && temp->value != NULL)
        {
            curr = temp->value; 
            cit = curr->person->value;
            vir = curr->disease->value;
            cntr = cit->origin->value;
            printf( "%d %s %s %s %d %s %s", cit->id, cit->firstname, cit->lastname, cntr->value, cit->age, vir->value, curr->vacc);
            if( curr->vaccDate != NULL)
            {
                printf("%d-%d-%d", curr->vaccDate->day, curr->vaccDate->month, curr->vaccDate->year);
            }
            printf("\n");
            temp = temp->next;
        }
    }
    else
    {
        if(type == 0)
        {
            virus *curr;
            while(temp != NULL && temp->value!=NULL)
            {
            curr = temp->value;
            printf("%s -> \n", curr->value);
            temp = temp->next;
            }
        }
        else
        {
            country *curr;
            while(temp != NULL && temp->value!=NULL)
            {
                curr = temp->value;
                printf("%s -> \n", curr->value);
                temp = temp->next;
            }
        }
    }
}

struct listnode* virusInList(char *value, list *virList)
{
    virus *left, *right; 
    listnode *front, *rear;
    int itemsLeft = virList->items; 
    front = virList->head;
    rear = virList->tail;
    while(itemsLeft > 0)
    {
        left = front->value;
        right = rear->value;
        if( strcmp(left->value, value) == 0 )
            return front;
        if ( strcmp(right->value, value) == 0 )
            return rear;
        if(virList->items == 1) /* only one item in list */
            return NULL;
        front = front->next;      
        rear = rear->previous; 
        itemsLeft-=2;
    }
    return NULL;
}

struct listnode* countryInList(char *value, list *cntrList)
{
    country *left, *right;
    listnode *front, *rear;
    int itemsLeft = cntrList->items;
    front = cntrList->head;
    rear = cntrList->tail;
    while(itemsLeft > 0)
    {
        left = front->value;
        right = rear->value;
        if( strcmp(left->value, value) == 0 )
            return front;
        if ( strcmp(right->value, value) == 0 )
            return rear;
        if(cntrList->items == 1) /* only one item in list */
            return NULL;
        front = front->next;
        rear = rear->previous;
        itemsLeft-=2;
    }
    return NULL;
}

record* recInList(int id, list *recList)
{
    record *left, *right;
    citizen *temp;
    listnode *front, *rear;
    int itemsLeft = recList->items;
    front = recList->head;
    rear = recList->tail;
    while(itemsLeft > 0)
    {
        left = front->value;
        temp = left->person->value;
        if(temp->id == id)
            return left;
        right = rear->value;
        temp = right->person->value;
        if( temp->id == id)
            return right;
        if(itemsLeft == 1)  /* only one item in list */
            return NULL;
        itemsLeft-=2;
    }

    return NULL;
}

void listDel(list *List, int type)
{
    struct listnode* node = List->head;
    
    while (node != NULL)
    {
        List->head = List->head->next;
        List->head->previous = NULL;
        
        if(type == 0)
            virusDel(node->value);
        else if(type == 1)
            countryDel(node->value);
        else if(type == 2)
            citizenDel(node->value);
        else
            recordDel(node->value);
        
        free(node);
        node = List->head;
    }
    free(List);
}
