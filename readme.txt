### Assignment 1 ###
Theodora Panagea 
1115201400135

-Current Folder: Original folder, contains all the following, as well as the Makefile: 
    |--Folder headers: Contains header files
    |--Folder src: Contains source files
    |--Folder inputs: Contains files with countries' & viruses' names, as well as the bash script 
                      that produces the input file. The input file is created at parent directory.
The executable can be located at parent folder, with the name vaccineMonitor, after running the command make all.

The data structures implemented are double linked lists which contain all the info, skip lists and bloom filters which use pointers to access data, in order to minimize data duplication.


BASH SCRIPT 
-----------
./testFile.sh virusesFile countriesFile numLines duplicatesAllowed

-virusesFile and countriesFile and text files with a virus/country per line.
-numLines is a positive number that indicates how many lines we want the file to have.
-duplicatesAllowed is a flag that indicates if a line with the same data (some of them) can be created. 

So, 
-It checks if given numbers are correct
-Creates an inputfile, each line being a record like the following ones: 
                                            889 John Papadopoulos Greece 52 COVID-19 YES 27-12-2020 
                                            889 John Papadopoulos Greece 52 Η1Ν1 ΝΟ
                                            776 Maria Tortellini Italy 36 SARS-1 NO
                                            125 Jon Dupont USA 76 H1N1 YES 30-10-2020
- ids and names are created randomly but two different people can't have same id and each id is unique. IF there are two people with same ID, the app will reject the second record. 
