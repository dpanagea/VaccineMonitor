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


    return 0;
}