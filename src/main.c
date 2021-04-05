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
    int argument;  /* num of args. to check if date is given */
    int id, age;    
    char first[13], last[13], origin[20], ans[4], dt[11], vir[20]; /* temp buffers */

    list *virList, *recList, *citList, *cntrList; /* lists */
    virList = listInit();   /* initialize */
    recList = listInit();
    citList = listInit();
    cntrList = listInit();
    listnode *temp, *cntrNode, *virNode, *citNode, *recNode; /* nodes for adding to lists. nodeCntr & nodeVir described below */
    record *rec;
    citizen *cit;
    virus *disease;
    country *cntr;
    date *dat;
    while (fgets(buf, 100, input) != NULL) 
    {
        argument = sscanf(buf, "%d %s %s %s %d %s %s %s ", &id, first, last, origin, &age, vir, ans, dt);
        if((argument == 8 && strcmp(ans, "YES") == 0) || (argument == 7 && strcmp(ans, "NO") == 0)) /* that means acceptable record */
        {   
            disease = virusDef(vir);    /* passes the temp buffer */
            cntr = countryDef(origin);  /* passes the temp buffer */
            if(argument == 8)
                dat = dateDef(dt);
            else   
                dat = NULL;

            virNode = virusInList(disease->value, virList); /* return the node if found */
            if(  virNode == NULL )              /* if virus not found, then you can add to list */
            {
                temp = nodeInit(disease);
                virNode = listAdd(temp, virList); 
            }  

            cntrNode = countryInList(cntr->value, cntrList);  /* return the node if found */
            if( cntrNode == NULL )                            /*if country not found, then you can add to list */
            {
                temp = nodeInit(cntr);
                cntrNode = listAdd(temp, cntrList); 
            }

            cit = citizenDef(id, first, last, cntrNode, age); /* passes all temp buffers & listnode pointers */
            if( recInList(cit->id, recList) == NULL )       /* if rec not found, then citizen doesn't exist already.
                                                                So, add both cit and rec to their lists. */
            {
                temp = nodeInit(cit);
                citNode = listAdd(temp, citList);

                rec= recordDef(citNode, virNode, ans, dat);
                temp = nodeInit(rec);
                recNode = listAdd(temp, recList);
            }
            else{}                                          /* if the recID exists, don't add to cit list BUT check if rec is valid. */
        }
        
    }
    //listPrint(virList, 0); Print List works fine -- 0 for virus
    //listPrint(cntrList, 1); 1 for country
    //listPrint(citList, 2); 2 for citizens
    //listPrint(recList, 3); 3 for records

    //listDel(recList, 3); haven't implemented anything on list Deletion
    //listDel(citList, 2);
    //listDel(cntrList, 1);
    //listDel(virList, 0);

    return 0;
}