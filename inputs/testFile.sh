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

for ((i = 1; i <= $numLines; i++))
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
    #check if id already exists. if duplicates allowed, then you can add.
    if [[ ! " ${id_array[@]} " =~ " ${id} " ]]; then #if not exist, then add, no prob
        id_array+=($id)
    else #id already exists, check duplicates variable. only when 1, add to array
        if [ $duplicates -eq "1" ]; then
            id_array+=($id)
        fi
    fi
done
#bubblesort for id_array
for ((i=0;i<"${#id_array[@]}";i++))
do
    for ((j=0;j<"${#id_array[@]}";j++))
    do
        if [[ ${id_array[$i]} -le "${id_array[$j]}" ]]; then
            t=${id_array[$i]}
            id_array[$i]=${id_array[$j]}
            id_array[$j]=$t
        fi
    done
done
echo ${id_array[@]}