#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "lists.h"
#include "bloom.h"

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

typedef struct country
{
    char* value;
}country;

typedef struct citizen
{
    int id;
    char* firstname;
    char* lastname;
    struct listnode* origin;
    int age;
}citizen;

typedef struct record
{
    struct listnode* person;
    struct listnode* disease;
    char* vacc;
    struct date* vaccDate;
}record;

struct virus* virusDef(const char*); 
struct date* dateDef(const char*); 
struct country* countryDef(const char*);
struct citizen* citizenDef(int, const char*, const char*, struct listnode*, int); 
struct record* recordDef(struct listnode*, struct listnode*, const char*, date*); 

int cmpDups(struct listnode*, struct citizen*, struct listnode*);

void virusDel(virus*);
void countryDel(country*);
void citizenDel(citizen*);
void recordDel(record*);

#endif
