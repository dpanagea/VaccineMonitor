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
                disease->bf = bloomInit(bloomSize);
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
            recNode = recInList(cit->id, recList);
            if( recNode == NULL )       /* if rec not found, then citizen doesn't exist already.
                                                                So, add both cit and rec to their lists. */
            {
                temp = nodeInit(cit);
                citNode = listAdd(temp, citList);
                rec= recordDef(citNode, virNode, ans, dat);
                temp = nodeInit(rec);
                recNode = listAdd(temp, recList);
            }
            else                                                    /* if the recID exists, don't add to cit list BUT check if rec is valid. */
            {
                if(cmpDups(recNode, cit, virNode) == 1)   /* if =1, then no conflict */
                {
                    rec = recNode->value;
                    citNode = rec->person;      /* find citizen pointer from 1st record */
                    rec = recordDef(citNode, virNode, ans, dat);    /* define the record we want to add to list */
                    temp = nodeInit(rec);
                    recNode = listAdd(temp, recList);
                } 
            }                                          
        }
        
    }
    // Print List works fine 
    //listPrint(virList, 0); 
    //listPrint(cntrList, 1);
    //listPrint(citList, 2); 
    //listPrint(recList, 3); 

    listDel(recList, 3); 
    listDel(citList, 2);
    listDel(cntrList, 1);
    listDel(virList, 0);

    return 0;
}