#include <stdio.h>
#include <time.h>
#include "../headers/functions.h"

int main(int argc, char* argv[])
{
    /* parsing */ 
    if (argc != 5)
    {
        printf ("Error: Wrong number of arguments \n Try .vaccineMonitor -c citizenRecordsFile -b bloomSize \n");
        return -1;
    }
    unsigned long bloomSize;
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
    int age;  
    char id[5], first[13], last[13], origin[20], ans[4], dt[11], vir[20]; /* temp buffers */

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
        argument = sscanf(buf, "%s %s %s %s %d %s %s %s ", id, first, last, origin, &age, vir, ans, dt);
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
                disease = virNode->value;
                disease->bf = bloomInit(bloomSize);
                disease->skip_no = skipInit();
                disease->skip_yes = skipInit();
            }  
            disease = virNode->value;
            cntrNode = countryInList(cntr->value, cntrList);  /* return the node if found */
            if( cntrNode == NULL )                            /*if country not found, then you can add to list */
            {
                temp = nodeInit(cntr);
                cntrNode = listAdd(temp, cntrList); 
            }

            cit = citizenDef(id, first, last, cntrNode, age); /* passes all temp buffers & listnode pointers */
            recNode = recInList(cit->id, recList);
            if( recNode == NULL )       /* if rec not found, then citizen doesn't exist already. So, add both cit and rec to their lists. */
            {
                temp = nodeInit(cit);
                citNode = listAdd(temp, citList);
                rec= recordDef(citNode, virNode, ans, dat);
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
            else                                                    /* if the recID exists, don't add to cit list BUT check if rec is valid. */
            {
                if(cmpDups(recNode, cit, virNode) == 1)   /* if =1, then no conflict */
                {
                    rec = recNode->value;
                    citNode = rec->person;      /* find citizen pointer from 1st record */
                    rec = recordDef(citNode, virNode, ans, dat);    /* define the record we want to add to list */
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
                else
                {
                    printf("ERROR IN RECORD %s", buf);
                }
            }                                          
        }
        else
        {
           printf("ERROR IN RECORD %s\n", buf);
        }
    }
/* ---------- END OF PROCESSING INPUT FILE --------------- */
    
    printf("Processing input file has ended.\n");
    while(1)
    {
        printf("Please insert the desired command\n");
        scanf("%s", buf);
        if(strcmp(buf, "/vaccineStatusBloom") == 0)
        {
            scanf("%s %s", id, vir);
            vaccineStatusBloom(virList, id, vir);
        }
        else if(strcmp(buf, "/vaccineStatus") == 0)
        {
            if( fgets(buf,100,stdin) != NULL)
                vaccineStatus(buf, virList);
        }
        else if(strcmp(buf, "/populationStatus") == 0)
        {

        }
        else if(strcmp(buf, "/popStatusByAge") == 0)
        {

        }
        else if(strcmp(buf, "/insertCitizenRecord") == 0)
        {
            if( fgets(buf, 100, stdin) != NULL)
                insertCitizenRecord(buf, virList, citList, recList, cntrList, bloomSize);
        }
        else if(strcmp(buf, "/vaccinateNow") == 0)
        {
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);

            date* curr; 
            curr->day = local->tm_mday;
            curr->month = local->tm_mon + 1;
            curr->year = local->tm_year + 1900;
            if(fgets(buf, 100, stdin) != NULL)
                vaccinateNow(buf, virList, curr);
        }
        else if(strcmp(buf, "/list-nonVaccinated-Persons") == 0)
        {
            if(fgets(buf, 100,stdin) != NULL)
                listNonVacc(buf, virList);
        }
        else if(strcmp(buf, "/exit") == 0)
        {
            printf("Exiting. We hope to see you again!\n");
            break;
        }
        else
        {
            printf("Wrong sequence of commands. Please try again.\n");
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