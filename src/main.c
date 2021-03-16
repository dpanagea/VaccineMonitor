#include "../headers/functions.h"

int main(int argc, char* argv[])
{
    /* parsing */ 
    if (argc != 5)
    {
        printf ("Error: Wrong number of arguments \n Try .vaccineMonitor -c citizenRecordsFile -b bloomSize \n");
        return -1;
    }
    int bloomSize;
    FILE *input;
    if (strcmp (argv[1], "-c") == 0 )
    {
        input = fopen(argv[2], "r");
        bloomSize = atoi(argv[4]);
    }
    else
    {
        input = fopen(argv[4], "r");
        bloomSize = atoi(argv[2]);
    }
    /* variables needed for arguments  */
    char buf[100]; /* line buffer */ 
    int argument;
    int id, age;
    char temp[20];
    char first[13], last[13], cntr[20], ans[4], dt[11], vir[20];
    /* lists */
    list *virs, *recs, *cits;
    virs = listInit();
    recs = listInit();
    cits = listInit();
    listnode *lnode;
    record *rec;
    citizen *cit;
    virus *disease;
    date *dat;
    while (fgets(buf, 100, input) != NULL)
    {
        argument = sscanf(buf, "%d %s %s %s %d %s %s %s ", &id, first, last, cntr, &age, vir, ans, dt);
        if((argument == 8 && strcmp(ans, "YES") == 0) || (argument == 7 && strcmp(ans, "NO") == 0))
        {   
            disease = virusDef(vir);
            if(argument == 8)
                dat = dateDef(dt);
            else   
                dat = NULL;
            cit = citizenDef(id, first, last, cntr, age);
            rec = recordDef(cit, disease, ans, dat);
            lnode = nodeInit(cit);
            listAdd(lnode, cits);
            /*
               1)find if virus already in list, else add it
               --------
               2)find if there is a duplicate in records. If there is, check
                 if the second rec can be added. If no duplicate found, 
                 add to records' and citizens' lists. 
            */
        //    recordDel(rec);
        }
        
    }
    listCitPrint(cits);

    return 0;
}