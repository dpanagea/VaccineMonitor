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
    date* dat = (date*)malloc(sizeof(date));
    sscanf(dt,"%d-%d-%d", &(dat->day), &(dat->month), &(dat->year));
    return dat;
}

citizen* citizenDef(int id, const char* first, const char* last, const char* cntr, int age)
{
    citizen* cit = (citizen*)malloc(sizeof(citizen));
    cit->id = id;
    cit->age = age;

    cit->firstname = (char*)malloc(sizeof(first));
    strcpy(cit->firstname, first);

    cit->lastname = (char*)malloc(sizeof(last));
    strcpy(cit->lastname, last);

    cit->country = (char*)malloc(sizeof(cntr));
    strcpy(cit->country,cntr);

    return cit; 
}

record* recordDef(citizen* cit, virus* vir, const char* ans, date* dat)
{
    record* rec = (record*)malloc(sizeof(record));

    rec->person = (citizen*)malloc(sizeof(citizen));
    rec->person = cit;

    rec->disease = (virus*)malloc(sizeof(virus));
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
/*
void recordDel(record* rec)
{

}
*/
