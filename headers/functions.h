#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "lists.h"

typedef struct date
{
    int day;
    int month;
    int year;
}date;

typedef struct virus
{
    char* value;
    void* skip_yes;
    void* skip_no;
    void* bloom;
}virus;

typedef struct citizen
{
    int id;
    char* firstname;
    char* lastname;
    char* country;
    int age;
}citizen;

typedef struct record
{
    struct citizen* person;
    struct virus* disease;
    char* vacc;
    struct date vaccDate;
}record;

struct virus* virusDef(char*); 
struct date* dateDef(char*); 
struct citizen* citizenDef(int, char*, char*, char*, int); 
struct record* recordDef(citizen*, virus*, char*, date*); 



#endif
