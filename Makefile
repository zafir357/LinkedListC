#On purge la liste des suffixes utilis? pour les r?les implicites
.SUFFIXES:

#On ajoute simplements les extensions dont l'on a besoin
.SUFFIXES:.c .o

#Nom de l'executable
EXEC=main

#Liste des fichiers sources separes par des espaces
SOURCES=main.c agenda.c
#Liste des fichiers objets
OBJETS=$(SOURCES:%.c=%.o)

#Compilateur et options de compilation
CCPP=gcc
LFLAGS=  -O0 -Wall -Wextra -std=c99 -g
CFLAGS= -std=c99 -g -O0 -Wall -Wextra


#R?le explicite de construction de l'ex?utable
$(EXEC):$(OBJETS) Makefile
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
main.o: main.c agenda.o
agenda.o: agenda.c agenda.h 								