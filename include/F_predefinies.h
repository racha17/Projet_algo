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
// algorithme de transformation
int priorite(char c);
int estOperateur(char c) ;
char sommetPile(Pile *pile);
char depiler(Pile *pile) ;
void empiler(Pile *pile, char element);
int pilePleine(Pile *pile);
int pileVide(Pile *pile);
void initPile(Pile *pile) ;
void depiler2(Pile *pile,int x);

#endif // F_PREDEFINIES_H_INCLUDED
