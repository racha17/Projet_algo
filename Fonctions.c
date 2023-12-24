#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
#include "F_predefenies.h"
#include "Fonctions.h"

void afficher(Pile *pile)
{
    int val;
    if (Pilevide(pile))
    {
        printf("la pile est vide\n");
        exit(EXIT_FAILURE);
    }

    Pile pile1 = initPile();

    while (!Pilevide(pile))
    {
        val = depiler(pile);
        printf("%d\n", val);
        empiler(&pile1, val);
    }
    while (!Pilevide(&pile1))
    {
        empiler(pile, depiler(&pile1));
    }

    printf("\n");
}
void suppression(Pile *pile, int val)
{

    Pile pile1;
    pile1.first = NULL;

    while (!Pilevide(pile))
    {
        int x = depiler(pile);
        if (x != val)
        {
            empiler(&pile1, x);
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }
    }
}