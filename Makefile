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

lists.o: src/lists.c headers/lists.h headers/functions.h
	@$(CC) -c $(FLG) src/lists.c

bloom.o: src/bloom.c headers/bloom.h headers/lists.h headers/functions.h
	@$(CC) -c $(FLG) src/bloom.c

functions.o: src/functions.c headers/functions.h headers/lists.h headers/bloom.h
	@$(CC) -c $(FLG) src/functions.c

vaccineMonitor: functions.o bloom.o lists.o
	@$(CC) -o vaccineMonitor src/main.c functions.o bloom.o lists.o
	@echo "-created vaccineMonitor"
