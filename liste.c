#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

struct list *creerListe(int N)
{
    int val;
    struct list *tete = (struct list *)malloc(sizeof(struct list));

    printf("donner une valeur:\n");
    scanf("%d", &val);
    tete->nbr = val;
    tete->svt = NULL;

    for (int i = 1; i < N; i++)
    {
        scanf("%d", &val);
        struct list *L = (struct list *)malloc(sizeof(struct list));
        L->svt = tete;
        L->nbr = val;
        tete = L;
    }

    return tete;
}
void afficher(struct list *tete)
{
    struct list *L = tete;
    while (L != NULL)
    {
        printf("%d -> ", L->nbr);
        L = L->svt;
    }
    printf("NULL\n");
}
void libererListe(struct list *tete)
{
    struct list *L;
    while (tete != NULL)
    {
        L = tete;
        tete = tete->svt;
        free(L);
    }
}
struct list *InsererElement(struct list *tete, int N, int val, int pos)
{
    struct list *L = tete;
    struct list *P = tete;

    if (pos == 1)
    {
        struct list *P1 = (struct list *)malloc(sizeof(struct list));
        P1->nbr = val;
        P1->svt = tete;
        tete = P1;
    }
    else if (pos == N)
    {
        while (L != NULL && L->svt != NULL)
        {
            L = L->svt;
        }
        if (L != NULL)
        {
            struct list *P1 = (struct list *)malloc(sizeof(struct list));
            P1->nbr = val;
            L->svt = P1;
            P1->svt = NULL;
        }
    }
    else
    {
        int i = 1;
        do
        {
            L = L->svt;
            P = L;
            i = i + 1;
        } while (i < pos - 1);
        P = P->svt;
        struct list *P1 = (struct list *)malloc(sizeof(struct list));
        P1->nbr = val;
        L->svt = P1;
        P1->svt = P;
    }
    return tete;
}
struct list *SuppElement(struct list *tete, int val)
{
    struct list *L = tete;
    struct list *P = tete->svt;
    if (tete->nbr == val)
    {
        tete = tete->svt;
        free(L);
        return tete;
    }

    while (P != NULL && P->svt != NULL)
    {
        if (P->nbr == val)
        {
            L->svt = P->svt;

            P = L->svt;
        }
        else
        {
            P = P->svt;
            L = L->svt;
        }
    }
    return tete;
    free(P);
}

int Recherche(struct list *tete, int val)
{
    int i = 1;
    struct list *P = tete;

    while (P != NULL)
    {
        if (P->nbr != val)
        {
            P = P->svt;
            i += 1;
        }
        else
        {
            return i;
        }
    }

    return -1;
}
struct list *TrieParSelection(struct list *tete)
{
    int X;
    struct list *P, *L;

    for (P = tete; P->svt != NULL; P = P->svt)
    {
        for (L = P->svt; L != NULL; L = L->svt)
        {
            if (P->nbr > L->nbr)
            {
                X = P->nbr;
                P->nbr = L->nbr;
                L->nbr = X;
            }
        }
    }

    return tete;
}
struct list *TrieParInsertion(struct list *tete)
{
}
