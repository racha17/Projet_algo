ProjetAlgo: main.o Fonctions.o F_predefinies.o 
	gcc main.o Fonctions.o F_predefinies.o -o ProjetAlgo

main.o: main.c structure.h
	gcc -c main.c
Fonctions.o: Fonctions.c Fonctions.h
	gcc -c Fonctions.c
F_predefenies.o: F_predefinies.c F_predefinies.h
	gcc -c F_predefinies.c
# stucture.o: structure.h
# 	gcc -c structure.h	
clean:
	rm *.o ProjetAlgo