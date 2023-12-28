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
    list *P;
    int x;
    while (!Pilevide(pile))
    {
        x = depiler(pile);
        if (x!=val)
        {
            empiler(&pile1, x);
        }

    }
    while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }

}
bool recherche(Pile *pile, int val)
{
    bool trouve;

    Pile R = initPile();
    trouve = false;

    while (!Pilevide(pile) && SommetPile(pile) != val)
    {
        empiler(&R, depiler(pile));
    }

    if (!Pilevide(pile))
    {
        trouve = true;
    }

    while (!Pilevide(&R))
    {
        empiler(pile, depiler(&R));
    }

    return trouve;
}


// Fonction pour vérifier si un caractère est un opérateur
int estOperateur(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}



// Fonction pour obtenir la priorité d'un opérateur
int priorite(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else {
        return 0;
    }
}
