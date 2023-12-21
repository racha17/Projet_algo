#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "liste.h"
int *creerTab(int max);
int *inserer(int *T, int max, int pos, int val);
int *suppval(int *T, int max, int val);
int *trieParSelection(int *T, int max);
int *trieParInsertion(int *T, int max);
int *trieParBulle(int *T, int max);

int *creerTab(int max)
{
    int *T = (int *)malloc(max * sizeof(int));

    printf("Faites entrer les valeurs du tableau:\n");
    for (int i = 0; i < max; i++)
    {
        scanf("%d", &T[i]);
    }
    return T;
}
int *inserer(int *T, int max, int pos, int val)
{
    if (pos < 0 || pos > max)
    {
        printf("position inexistante");
        return T;
    }
    int *T1 = (int *)malloc((max + 1) * sizeof(int));
    for (int i = 0; i < pos; i++)
    {
        T1[i] = T[i];
    }
    T1[pos] = val;
    for (int i = pos; i < max; i++)
    {
        T1[i + 1] = T[i];
    }
    free(T);
    return T1;
}
int *suppval(int *T, int max, int val1)
{
    int occ = 0;
    for (int i = 0; i < max; i++)
    {
        if (T[i] == val1)
        {
            occ = occ + 1;
        }
    }

    int *T1 = (int *)malloc((max - occ) * sizeof(int));
    int j = 0;
    for (int i = 0; i < max; i++)
    {
        if (T[i] != val1)
        {
            T1[j] = T[i];
            j += 1;
        }
    }
    free(T);
    return T1;
}
int *trieParSelection(int *T, int max)
{
    int iMin, X;
    for (int i = 0; i < max - 1; i++)
    {
        iMin = i;
        for (int j = i + 1; j < max; j++)
        {
            if (T[j] < T[iMin])
            {
                iMin = j;
            }
        }
        X = T[iMin];
        T[iMin] = T[i];
        T[i] = X;
    }
    return T;
}
int *trieParInsertion(int *T, int max)
{
    int i, j, Y;
    for (i = 1; i < max; i++)
    {
        Y = T[i];
        j = i - 1;
        while (j >= 0 && T[j] > Y)
        {
            T[j + 1] = T[j];
            j = j - 1;
        }
        T[j + 1] = Y;
    }
    return T;
}
int *trieParBulle(int *T, int max)
{
    int i, j, Z;
    bool perm = true;
    i = 0;
    while (i < max - 1 && perm == true)
    {
        perm = false;
        for (j = 0; j < max - 1; j++)
        {
            if (T[j] > T[j + 1])
            {
                Z = T[j];
                T[j] = T[j + 1];
                T[j + 1] = Z;
                perm = true;
            }
            i = i + 1;
        }
    }
    return T;
}

int main(int argc, char const *argv[])
{
    /*int max;
    int *T;
    printf("donnez la taille maximale de max:\n");
    scanf("%d", &max);

    T = creerTab(max);

    printf("les elements du tableau sont:\n");
    for (int i = 0; i < max; i++)
    {
        printf("%d\t", T[i]);
    }
    printf("\n");
    int pos, val;
    printf("donnez une position superieur a 0 et inferieur a max:\n");
    scanf("%d", &pos);
    printf("\n");
    printf("donnez la valeur a inserer\n");
    scanf("%d", &val);
    T = inserer(T, max, pos, val);
    printf("les valeurs du tableau apres insertion:\n");
    for (int i = 0; i <= max; i++)
    {
        printf("%d\t", T[i]);
    }
    printf("\n");
    int val1;
    printf("donner une valeur a supprimer:\n");
    scanf("%d", &val1);
    T = suppval(T, max, val1);
    printf("\n");
    printf("tableau apres suppression de l'element:\n");
    for (int i = 0; i < max - 1; i++)
    {
        printf("%d\t", T[i]);
    }
    printf("\n");
    printf("donnez une valeur a chercher dans le tableau:\n");
    scanf("%d\n",&val);
    i=recherche(T,max,val);
    printf("la valeur %d est a la position %d:\n",val,i);
    printf("tableau apres le trie par insertion:\n");
    T = trieParInsertion(T, max);
    for (int i = 0; i < max; i++)
    {
        printf("%d\t", T[i]);
    }
    printf("\n");

    printf("tableau apres le trie par bulle:\n");
     T=trieParBulle(T,max);
     for (int i = 0; i < max; i++)
    {
        printf("%d\t", T[i]);
    }
    printf("\n");

    free(T);
    */

    int N;
    int val, pos, i;

    printf("donner le nombre d'elements de la liste:\n");
    scanf("%d", &N);
    struct list *tete = creerListe(N);
    printf("donner une valeur a inserer:\n");
    scanf("%d", &val);
    printf("donner une position ou inserer:\n");
    scanf("%d", &pos);
    tete = InsererElement(tete, N, val, pos);
    afficher(tete);
    printf("donner une valeur a supprimer:\n");
    scanf(" %d", &val);
    tete = SuppElement(tete, val);
    afficher(tete);
    printf("donner une valeur a chercher:\n");
    scanf("%d", &val);
    i = Recherche(tete, val);
    printf("La valeur %d est a la position: %d\n", val, i);
    printf("la liste apres le trie par selection :\n");
    tete = TrieParSelection(tete);
    afficher(tete);
    libererListe(tete);

    return 0;
}
