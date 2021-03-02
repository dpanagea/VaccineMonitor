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
    echo "numLines is either not a number or <0"; exit -1
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
i=1
while [ "$i" -le $numLines ]
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
    #if id doesn't exist, then create record
    if [[ ! " ${id_array[@]} " =~ " ${id} " ]]; then 
        id_array+=($id)
        #random names
        fname=$(cat /dev/urandom | tr -dc 'A-Za-z' | fold -w 5 | head -n 1)
        lname=$(cat /dev/urandom | tr -dc 'A-Za-z' | fold -w 9 | head -n 1)
        #random country from txt
        country=$(shuf $countriesFile -n 1) 
        #random age
        ageLow=1
        ageHigh=120
        age=0
        while [ "$age" -le $ageLow ]
        do
            age=$RANDOM
            let "age %= ageHigh"
        done
        #random virus from txt 
        virus=$(shuf $virusesFile -n 1)
        #random answer YES/NO
        B=2
        bin=$RANDOM
        let "bin %= B"
        if [ "$bin" -eq 1 ]; then
            vacc=YES
            #we need to create random date
            #days
            dayLow=1
            dayHigh=30
            day=0
            while [ "$day" -le $dayLow ]
            do
                day=$RANDOM
                let "day %= dayHigh"
            done
            #month
            monthLow=1
            monthHigh=12
            month=0
            while [ "$month" -le $monthLow ]
            do
                month=$RANDOM
                let "month %= monthHigh"
            done
            yearLow=1990
            yearHigh=2021
            year=0
            while [ "$year" -le $yearLow ]
            do
                year=$RANDOM
                let "year %= yearHigh"
            done
            echo "$id $fname $lname $country $age $virus $vacc $day-$month-$year" >> ../inputFile
        else 
            vacc=NO
            echo "$id $fname $lname $country $age $virus $vacc" >> ../inputFile
        fi
        #check if this id will be duplicated
        if [ "$duplicates" -eq 1 ]; then
            ran=$RANDOM
            let "ran %= 100"
            #if duplicated, then we will keep id, name, country & age the same
            if [ "$ran" -le 1 ]; then 
                #random virus from txt 
                virus=$(shuf $virusesFile -n 1)
                #random answer YES/NO
                B=2
                bin=$RANDOM
                let "bin %= B"
                if [ "$bin" -eq 1 ]; then
                    vacc=YES
                    #we need to create random date
                    #days
                    dayLow=1
                    dayHigh=30
                    day=0
                    while [ "$day" -le $dayLow ]
                    do
                        day=$RANDOM
                        let "day %= dayHigh"
                    done
                    #month
                    monthLow=1
                    monthHigh=12
                    month=0
                    while [ "$month" -le $monthLow ]
                    do
                        month=$RANDOM
                        let "month %= monthHigh"
                    done
                    yearLow=1990
                    yearHigh=2021
                    year=0
                    while [ "$year" -le $yearLow ]
                    do
                        year=$RANDOM
                        let "year %= yearHigh"
                    done
                    echo "$id $fname $lname $country $age $virus $vacc $day-$month-$year" >> ../inputFile
                else 
                    vacc=NO
                    echo "$id $fname $lname $country $age $virus $vacc" >> ../inputFile
                fi
                let "i = i+1"
            fi
        fi
        let "i = i+1"
    fi
done


