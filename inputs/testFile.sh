#!/bin/bash

#instead of using just the arguments, I use variables to make the script easier to read
virusesFile=$1
countriesFile=$2
numLines=$3
duplicates=$4

#check if correct num of args is given. Else error message and exit
if [ "$#" -ne 4 ]; then
    echo "Error: Not enough arguments."; exit -1
fi 

#check if numLines is a positive number
[ -n "$3" ] && [ "$3" -eq "$3" ] && [ $3 -gt 0 ] 2>/dev/null    
if [ $? -ne 0 ]; then
    echo "numFilesPerDirectory input is either not a number or <0"; exit -1
fi

#check if duplicatesAllowed is 0 or 1
if [ $duplicates -ne 0 ] && [ $duplicates -ne 1 ]; then
    echo "Error: duplicatesAllowed should be 0 or 1"; exit -1
fi

#check if given files do exist
if [ ! -f "virusesFile" ]; then
    echo "Error: File with viruses doesn't exist."; exit -1
fi
if [ ! -f "countriesFile" ]; then
    echo "Error: File with countries doesn't exist."; exit -1
fi

#create file
file="inputFile"
touch $file
declare -a id_array 
#if duplicates are allowed, then I want 1% chance for a rec to have a duplicate
for ((i = 1; i <= $((numLines-numdups)); i++))
do
    #random id
    idLow=0
    idHigh=9999
    id=0
    while [ "$id" -le $idLow ]
    do
        id=$RANDOM 
        let "id %= idHigh"
    done
    #if id doesn't exist, then add it
    if [[ ! " ${id_array[@]} " =~ " ${id} " ]]; then 
        id_array+=($id)
        fname=$(cat /dev/urandom | tr -dc 'A-Za-z' | fold -w 12 | head -n 1)
        lname=$(cat /dev/urandom | tr -dc 'A-Za-z' | fold -w 12 | head -n 1)
        country=$(shuf $countriesFile -n 1) 
        virus=$(shuf $virusesFile -n 1)
        echo "$id: $fname $lname $country $virus"
    fi
    if [ "$duplicates" -eq 1 ]; then
        ran=-1
        while [ "$ran" -le 0 ]
        do
            ran=$RANDOM
            let "ran %= 100"
        done
        if [ "$ran" -le 1 ]; then
            id_array+=($id)
            let "i = i+1"
        fi
    fi
done


echo ${id_array[@]}