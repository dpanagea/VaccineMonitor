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
    char vacc;
    struct date vaccDate;
}record;

struct record* recordDef(char* buf); /*From buffer, create record */
struct citizen* citizenDef(char* buf); /*From buffer, create citizen */
struct virus* virusDef(char* buf); /*From buffer, create virus */
struct date* dateDef(char* buf); /*From buffer, create date */


#endif
