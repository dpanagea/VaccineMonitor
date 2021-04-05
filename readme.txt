### Assignment 1 ###
Theodora Panagea 
1115201400135

-Folder hw1: Original folder, contains all the following folder, as well as the Makefile: 
    |--Folder headers: Contains header files
    |--Folder src: Contains source files
    |--Folder inputs: Contains files with countries' & viruses' names, as well as the script 
                      that produces the input file. The input file is created at parent directory.
The executable can be located at hw1 folder, with the name vaccineMonitor

-functions.c/.h : Contains structs (at .h) and definitive functions about them.
    |--Struct date
    |--Struct virus: string with virus' name, and pointers that show to desired data structures.
    |                3 such pointers, 1 for skiplist with vaccinated people (skip_yes), 
    |                1 for skiplist with non-vaccinated people (skip_no), and 1 for the bloomfilter(bloom).
    |--Struct country: a string for a country's name
    |--Struct citizen: All required info that makes a citizen. That is id, name, country, and age. 
    |                  Instead of a string with country's name, we have a pointer for the exact country
    |                  at countries' list. 
    |--Struct record: Record consists of a citizen (pointer to a list), virus (pointer to a list), a string
    |                 with an answer about whether the citizen is vaccinated or not for the aforementioned virus.
    |                 If yes, a vaccination date is expected to follow.
    |-- All def functions take as arguments buffers that contain the values we need to save to a struct. 
    |                 They return a pointer to that struct.
    |--All del functions handle the free() for the corresponding data structs.

-