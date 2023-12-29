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

#endif // F_PREDEFINIES_H_INCLUDED
