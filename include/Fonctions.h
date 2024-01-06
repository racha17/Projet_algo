#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "structure.h"
#include <stdbool.h>
void afficher(Pile *pile);
bool suppression(Pile *pile, int val);
void insertion(Pile *pile, int val);
bool recherche(Pile *pile, int val);
void transformerExpression(char *expression);
#endif // FONCTIONS_H_INCLUDED
