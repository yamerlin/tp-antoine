#On purge la liste des suffixes utilis? pour les r?les implicites
.SUFFIXES:

#On ajoute simplements les extensions dont l'on a besoin
.SUFFIXES:.c .o

#Nom de l'executable
EXEC=main

#Liste des fichiers sources separes par des espaces
SOURCES=main.c addEvent.c createEvent.c deleteEvent.c loadCalendar.c printCalendar.c saveCalendar.c testInput.c convertInputToString.c
#Liste des fichiers objets
OBJETS=$(SOURCES:%.c=%.o)

#Compilateur et options de compilation
CCPP=gcc
LFLAGS=  -O0 -Wall -Wextra -std=c99 -g
CFLAGS= -std=c99 -g -O0 -Wall -Wextra


#R?le explicite de construction de l'ex?utable
$(EXEC):$(OBJETS)
	$(CCPP) -o  $(EXEC) $(OBJETS) $(LFLAGS)
.c.o:
	$(CCPP) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm $(OBJETS)
clear:
	rm $(EXEC)
depend:
	sed -e "/^#DEPENDANCIES/,$$ d" Makefile >dependances
	echo "#DEPENDANCIES" >> dependances
	$(CCPP) -MM $(SOURCES) >> dependances
	cat dependances >Makefile
	rm dependances

#DEPENDANCIES
main.o: main.c addEvent.o createEvent.o deleteEvent.o loadCalendar.o printCalendar.o saveCalendar.o testInput.o convertInputToString.o nodeStruct.h 
addEvent.o: addEvent.c nodeStruct.h
createEvent.o: createEvent.c nodeStruct.h addEvent.o testInput.o convertInputToString.o
deleteEvent.o: deleteEvent.c nodeStruct.h testInput.o convertInputToString.o
loadCalendar.o: loadCalendar.c nodeStruct.h addEvent.o
printCalendar.o: printCalendar.c nodeStruct.h
saveCalendar.o: saveCalendar.c nodeStruct.h
testInput.o: testInput.c
convertInputToString.o: convertInputToString.c

