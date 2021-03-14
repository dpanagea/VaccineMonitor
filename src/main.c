#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    /* -----------------------------  */
    char buf[100]; /* line buffer */ 
    int numargs;
    while (fgets(buf, 100, input) != NULL)
    {
        record* rec;
        citizen* cit;
        virus* disease;
        date* dat;
        int id, age;
        char first[13], last[13], cntr[20], ans[4], date[11], vir[20]; 

        numargs = sscanf(buf, "%d %s %s %s %d %s %s %s\n",
                        &id, first, last, cntr, &age, vir, ans, date);
        if((numargs==8 && !strcmp(ans, "yes")) || (numargs==7 && !strcmp(ans, "no"))) /* strcmp when equal, returns 0 */
        {
            disease = virusDef(vir);
            dat = dateDef(date);
            cit = citizenDef(id, first, last, cntr, age);
            rec = recordDef(cit, disease, ans, dat);
        }
    }


    return 0;
}