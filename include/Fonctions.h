#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "structure.h"
#include <stdbool.h>
void afficher(Pile *pile);
bool suppression(Pile *pile, int val);

void insertion(Pile *pile, int val, int Pos);

bool recherche(Pile *pile, int val);

#endif // FONCTIONS_H_INCLUDED
