#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
#include "F_predefinies.h"

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

void initPileAT(Pile *pile) {
    pile->top = -1;
}

int pileVideAT(Pile *pile) {
    return pile->top == -1;
}

int pilePleine(Pile *pile) {
    return pile->top == MAX_TAILLE_EXPRESSION - 1;
}

void empilerAT(Pile *pile, char element) {
    if (!pilePleine(pile)) {
        pile->items[++pile->top] = element;
    } else {
        printf("Erreur : la pile est pleine.\n");
        exit(EXIT_FAILURE);
    }
}

char depilerAT(Pile *pile) {
    if (!pileVide(pile)) {
        return pile->items[pile->top--];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

char sommetPileAT(Pile *pile) {
    if (!pileVide(pile)) {
        return pile->items[pile->top];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
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
