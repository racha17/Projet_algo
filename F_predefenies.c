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
