#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
#include "F_predefenies.h"

Pile initPile()
{
    Pile *p = malloc(sizeof(Pile));
    p->first = NULL;
    return *p;
}

bool Pilevide(Pile *pile)
{
    return pile->first == NULL;
}

int SommetPile(Pile *pile)
{
    if (Pilevide(pile))
    {
        exit(EXIT_FAILURE);
    }
    return pile->first->nbr;
}

void empiler(Pile *pile, int val)
{

    list *L = malloc(sizeof(list));
    if (L == NULL)
    {
        exit(EXIT_FAILURE);
    }

    L->nbr = val;
    L->svt = pile->first;
    pile->first = L;
}

int depiler(Pile *pile)
{
    int nbrdepile = 0;
    list *L = pile->first;
    if (Pilevide(pile))
    {
        exit(EXIT_FAILURE);
    }

    if (L != NULL)
    {
        nbrdepile = L->nbr;
        pile->first = L->svt;
        free(L);
    }
    return nbrdepile;
}
/* les fonction predefinies pour l'algorithme de transformation parce que il utilise la representation contigue*/

typedef struct {
    char items[MAX_TAILLE_EXPRESSION];
    int top;
} Pile;

void initPile2(Pile *pile) {
    pile->top = -1;
}

int pileVide2(Pile *pile) {
    return pile->top == -1;
}

int pilePleine(Pile *pile) {
    return pile->top == MAX_TAILLE_EXPRESSION - 1;
}

void empiler(Pile *pile, char element) {
    if (!pilePleine(pile)) {
        pile->items[++pile->top] = element;
    } else {
        printf("Erreur : la pile est pleine.\n");
        exit(EXIT_FAILURE);
    }
}

char depiler(Pile *pile) {
    if (!pileVide(pile)) {
        return pile->items[pile->top--];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

char sommetPile(Pile *pile) {
    if (!pileVide(pile)) {
        return pile->items[pile->top];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

