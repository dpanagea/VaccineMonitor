#include "../headers/functions.h"

virus* virusDef(const char *vir)
{
    virus *curr = (virus*)malloc(sizeof(virus));
    curr->value = (char*)malloc(sizeof(vir));
    if(curr->value == NULL){printf("Error \n");}
    strcpy(curr->value, vir);
    curr->bf = NULL;
    curr->skip_no = NULL;
    curr->skip_yes = NULL; 

    return curr;
}

date* dateDef(const char* dt)
{
    date* curr = (date*)malloc(sizeof(date));
    sscanf(dt,"%d-%d-%d", &(curr->day), &(curr->month), &(curr->year));

    return curr;
}

country* countryDef(const char* cntr)
{
    country* curr; 
    curr = (country*)malloc(sizeof(country));
    curr->value = (char*)malloc(sizeof(cntr));
    strcpy(curr->value, cntr);

    return curr;
}

citizen* citizenDef(const char* id, const char* first, const char* last, struct listnode *cntr, int age)
{
    citizen* curr = (citizen*)malloc(sizeof(citizen));
    curr->age = age;

    curr->id = (char*)malloc(sizeof(id));
    strcpy(curr->id, id);

    curr->firstname = (char*)malloc(sizeof(first));
    strcpy(curr->firstname, first);

    curr->lastname = (char*)malloc(sizeof(last));
    strcpy(curr->lastname, last);

    curr->origin = cntr;
    
    return curr; 
}

record* recordDef(struct listnode* cit, struct listnode* vir, const char* ans, date* dat)
{
    record* rec = (record*)malloc(sizeof(record));

    rec->person = cit;
    rec->disease = vir;
    
    rec->vacc = (char*)malloc(sizeof(ans));
    strcpy(rec->vacc,ans);

    if(strcmp(rec->vacc, "YES") == 0)
    {
        rec->vaccDate = (date*)malloc(sizeof(date));
        rec->vaccDate = dat;
    }
    else
        rec->vaccDate = NULL;
        
    return rec;
}

int cmpDups(struct listnode* recNode, citizen* cit2, struct listnode* virNode)
{
    record* rec = recNode->value;
    citizen* cit1 = rec->person->value;
    if (strcmp(cit1->id, cit2->id) != 0){return 0;}
    else if(strcmp(cit1->firstname, cit2->firstname) != 0){return 0;}
    else if(strcmp(cit1->lastname, cit2->lastname) != 0){return 0;}
    else if(strcmp(cit1->origin->value, cit2->origin->value) != 0){return 0;}
    else if(cit1->age != cit2->age){return 0;}
    else if(strcmp(rec->disease->value, virNode->value) == 0){return 0;} /* the last rec has the same virus as the 1st */
    return 1;
}

void virusDel(virus* temp)
{
    free(temp->value);
    free(temp);
}

void countryDel(country* temp)
{
    free(temp->value);
    free(temp);
}

void citizenDel(citizen* temp)
{
    free(temp->id);
    free(temp->firstname);
    free(temp->lastname);
    free(temp);
}

void recordDel(record* temp)
{
    free(temp->vacc);
    free(temp->vaccDate);
    free(temp);
}
