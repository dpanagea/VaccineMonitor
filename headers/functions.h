#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAXK 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "skip.h"
#include "bloom.h"

typedef struct list list;

typedef struct date
{
    int day;
    int month;
    int year;
}date;

typedef struct virus
{
    char* value;
    struct skiplist* skip_yes;
    struct skiplist* skip_no;
    struct bloom* bf;
}virus;

typedef struct country
{
    char* value;
}country;

typedef struct citizen
{
    char* id;
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
struct citizen* citizenDef(const char*, const char*, const char*, struct listnode*, int); 
struct record* recordDef(struct listnode*, struct listnode*, const char*, date*); 

int cmpDups(struct listnode*, struct citizen*, struct listnode*);

void virusDel(virus*);
void countryDel(country*);
void citizenDel(citizen*);
void recordDel(record*);

/* Commands asked from assignment */
void vaccineStatusBloom(list*, char*, char*);
void vaccineStatus(char*, list*);
void insertCitizenRecord(char*, list*, list*, list*, list*, int);
void vaccinateNow(char*, list*, date*);
void listNonVacc(char*, list*);

#endif
