#include "../headers/functions.h"

virus* virusDef(const char *vir)
{
    virus *curr = (virus*)malloc(sizeof(virus));
    curr->value = (char*)malloc(sizeof(vir));
    if(curr->value == NULL){printf("Error \n");}
    strcpy(curr->value, vir);
    curr->bloom = NULL;
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

citizen* citizenDef(int id, const char* first, const char* last, struct listnode *cntr, int age)
{
    citizen* curr = (citizen*)malloc(sizeof(citizen));
    curr->id = id;
    curr->age = age;

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