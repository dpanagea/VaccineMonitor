VPATH=./src/:./headers/

RM := rm -f
CC := gcc
FLG := -Wall -pedantic -Wextra -Wpointer-arith
FLG += -Wshadow -Wfloat-equal -Waggregate-return

all: vaccineMonitor
	@echo ">linking finished"
	@echo "Run: ./vaccineMonitor -c citizenRecordsFile -b bloomSize"
	@$(RM) *.o
clean: 
	@$(RM) vaccineMonitor 
	@$(RM) *.o

lists.o: src/lists.c headers/lists.h 
	@$(CC) -c $(FLG) src/lists.c

hashtable.o: src/hashtable.c headers/hashtable.h headers/lists.h
	@$(CC) -c $(FLG) src/hashtable.c

functions.o: src/functions.c headers/functions.h headers/lists.h headers/hashtable.h
	@$(CC) -c $(FLG) src/functions.c

vaccineMonitor: functions.o hashtable.o lists.o
	@$(CC) -o vaccineMonitor src/main.c functions.o hashtable.o lists.o
	@echo "-created vaccineMonitor"
