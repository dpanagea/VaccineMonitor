#include "../headers/functions.h"
#include "../headers/lists.h"

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
    else if(strcmp(rec->disease->value, virNode->value) == 0){return 2;} /* the last rec has the same virus as the 1st */
    return 1;
}

void virusDel(virus* temp)
{
    free(temp->value);
    bloomDel(temp->bf);
    skipDel(temp->skip_yes);
    skipDel(temp->skip_no);
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

/* --------- Applications/Commands asked from assignment ----------- */

void vaccineStatusBloom(struct list* virList, char* id, char* vir)
{
    listnode* lnode = virusInList(vir, virList);
    virus* disease;
    int vacc;
    if (lnode == NULL)
    {
        printf("Disease '%s' not found in our records. \n", vir);
    }
    else
    {
        disease = lnode->value;
        vacc = bloomFind(disease->bf, id);
        if (vacc == 0)
            printf("NOT VACCINATED \n");
        else
            printf("MAYBE\n");
    }
}

void vaccineStatus(char* buf, struct list* virList)
{
    char id[5], vir[20], err[20];
    int args = sscanf(buf, "%s %s %s", id, vir, err);
    if(args == 1)
    {
        virus *curr;
        listnode *temp = virList->head;
        while (temp != NULL && temp->value != NULL)
        {
            curr = (virus*)temp->value;
            snode *yes = NULL, *no= NULL;
            yes = skipFind(curr->skip_yes, id);
            if(yes == NULL)
            {
                no = skipFind(curr->skip_no, id);
                if (no != NULL)
                    printf("%s NO\n", curr->value);    
            }
            else
            {
                record *rec = (record*)yes->value;
                printf("%s %s %d-%d-%d\n", curr->value, rec->vacc, rec->vaccDate->day, rec->vaccDate->month, rec->vaccDate->year);
            }
            temp = temp->next;
        }
    }
    else if(args == 2)
    {
        listnode *lnode = virusInList(vir, virList);
        if(lnode == NULL)
        {
            printf("Disease '%s' not found in our records.\n", vir);
        }
        else
        {
            virus* disease = (virus*) lnode->value;
            snode *yes = NULL , *no = NULL;
            yes = skipFind(disease->skip_yes, id);
            no = skipFind(disease->skip_no, id);
            if(yes == NULL)
            {
                if(no == NULL)
                    printf("Not enough data about citizen %s and virus '%s'.\n", id, vir);
                else
                    printf("NOT VACCINATED\n");
            }
            else
            {
                record *rec = (record*)yes->value;
                printf("VACCINATED ON %d-%d-%d \n", rec->vaccDate->day, rec->vaccDate->month, rec->vaccDate->year);
            }
        }
    }
    else
        printf("Wrong number of arguments in 'vaccineStatus'. Try again \n");
}

void insertCitizenRecord(char* buf, list* virList, list* citList, list* recList, list* cntrList, int bloomSize)
{
    int age;
    char id[5], first[13], last[13], origin[20], ans[4], dt[11], vir[20];
    int args = sscanf(buf, "%s %s %s %s %d %s %s %s ",id, first, last, origin, &age, vir, ans, dt);
    if((args == 8 && strcmp(ans, "YES") == 0) || (args == 7 && strcmp(ans, "NO") == 0))
    {
        virus *disease = virusDef(vir);
        country *cntr = countryDef(origin);
        record *rec;
        date *dat;
        listnode *temp, *cntrNode, *virNode, *citNode, *recNode;
        if(args == 8)
            dat = dateDef(dt);
        else
            dat = NULL;
        virNode = virusInList(disease->value, virList);
        if(virNode == NULL) /* new virus */
        {
            temp = nodeInit(disease);
            virNode = listAdd(temp, virList);
            disease = virNode->value;
            disease->bf = bloomInit(bloomSize);
            disease->skip_no = skipInit();
            disease->skip_yes = skipInit();
        }
        disease = virNode->value;
        cntrNode = countryInList(cntr->value, cntrList);
        if(cntrNode == NULL)
        {
            temp = nodeInit(cntr);
            cntrNode = listAdd(temp, cntrList);
        }
        citizen *cit = citizenDef(id, first, last, cntrNode, age);
        recNode = recInList(cit->id, recList);
        if (recNode == NULL) /* rec with citID not found */
        {
            temp = nodeInit(cit);
            citNode = listAdd(temp, citList);
            rec = recordDef(citNode, virNode, ans, dat);
            temp = nodeInit(rec);
            recNode = listAdd(temp, recList);
            if (strcmp(ans, "YES") == 0)
            {
                bloomAdd(disease->bf, cit->id);
                skipAdd(disease->skip_yes, rec);
            }
            else
                skipAdd(disease->skip_no, rec);
        }
        else
        {
            int f = cmpDups(recNode, cit, virNode);
            rec = recNode->value;
            citNode = rec->person;
            if( f == 1) /* no conflicts */
            { 
                rec = recordDef(citNode, virNode, ans, dat);
                temp = nodeInit(rec);
                recNode = listAdd(temp, recList);
                if(strcmp(ans, "YES") == 0)
                {
                    bloomAdd(disease->bf, cit->id);
                    skipAdd(disease->skip_yes, rec);
                }
                else
                    skipAdd(disease->skip_no, rec);
            }
            else if (f == 2) /* same virus. if not vaccinated, update. if vaccinated, error message */
            { 
                if(strcmp(rec->vacc, "YES") == 0)
                    printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %d-%d-%d\n", cit->id, rec->vaccDate->day, rec->vaccDate->month, rec->vaccDate->year);
                else if(strcmp(ans, "YES") == 0)
                {
                    printf("Updating citizen %s info\n", cit->id);
                    rec->vacc = (char*)realloc(rec->vacc, sizeof(ans));
                    strcpy(rec->vacc, ans);
                    rec->vaccDate = dat;
                }
            }
            else 
                printf("Error in given data\n");
        }
    }
    else
    {
        printf("Error in given record. Wrong arguments.\n");
    }
}

void vaccinateNow(char* buf, list* virList, date* dt)
{
    int age; 
    char id[5], first[13], last[13], origin[20], ans[4], vir[20];
    sscanf(buf,"%s %s %s %s %d %s", id, first, last, origin, &age, vir);
    listnode *virNode = NULL;
    virus *disease = virusDef(vir);
    record *rec; 
    snode *yes = NULL, *no = NULL;
    char yn[4];
    int add = 0; /* no need to add new record */
    virNode = virusInList(disease->value, virList);
    if(virNode == NULL)
    {
        printf("Virus %s not in our records. Want to add now and insert the new record? (yes/no)\n", vir);
        scanf("%s", yn);
        if(strcmp(yn, "yes") == 0)
            add = 1;
    }
    else
    {
        disease = (virus*)virNode->value;
        yes = skipFind(disease->skip_yes, id);
        
        if(yes != NULL)
        {
            no = skipFind(disease->skip_no, id);
            printf("There is no record regarding citizen %s and virus %s. Want to add now? (yes/no)\n", id, vir);
            scanf("%s", yn);
            if(strcmp(yn, "yes") == 0)
                add = 1;
            if(no != NULL)
            {
                rec = (record*)no->value;
                snodeDel(disease->skip_no, no);
                rec->vacc = (char*)realloc(rec->vacc, sizeof(ans));
                strcpy(rec->vacc, ans);
                rec->vaccDate->day = dt->day;
                rec->vaccDate->month = dt->month;
                rec->vaccDate->year = dt->year;
                skipAdd(disease->skip_yes, rec);
            }

            rec = (record*)yes->value;
            
        

            printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %d-%d-%d\n", id, rec->vaccDate->day, rec->vaccDate->month, rec->vaccDate->year);
        }
    }
}

void listNonVacc(char* buf, list* virList)
{
    char vir[20];
    int args = sscanf(buf, "%s", vir);
    if(args == 1)
    {
        listnode *lnode = virusInList(vir,virList);
        if(lnode != NULL)
        {
            virus *disease = (virus*) lnode->value;
            skip *slist = disease->skip_no;
            snode *curr;
            record *rec;
            citizen *cit;
            country *cntr;
            curr = slist->levels[0];
            curr = curr->next;
            while(curr != NULL)
            {
                rec = (record*)curr->value;
                cit = (citizen*)rec->person->value;
                cntr = (country*)cit->origin->value;
                printf("%s %s %s %s %d \n", cit->id, cit->firstname, cit->lastname, cntr->value, cit->age);
                curr = curr->next;
            }
        }
    }
}