#ifndef F_PREDEFINIES_H_INCLUDED
#define F_PREDEFINIES_H_INCLUDED
#include <stdbool.h>
#include "Structure.h"

Pile initPile();
bool Pilevide(Pile *pile);
int SommetPile(Pile *pile);
void empiler(Pile *pile, int val);
int depiler(Pile *pile);
void afficher(Pile *pile);

/* pour l'algorithme de transformation */
void empiler(Pile *pile, char element);
int pilePleine(Pile *pile);
char depiler(Pile *pile);
char sommetPile(Pile *pile);
int pileVide2(Pile *pile);
void initPile2(Pile *pile);


#endif // F_PREDEFINIES_H_INCLUDED
