#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int nbr;
    struct list *svt;
} list;

typedef struct Pile
{
    list *first;
} Pile;

void empiler(Pile *pile, int val)
{
    list *L = malloc(sizeof(*L));
    if (pile == NULL || L == NULL)
    {
        exit(EXIT_FAILURE);
    }

    L->nbr = val;
    L->svt = pile->first;
    pile->first = L;
}

void afficher(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    list *P = pile->first;
    while (P != NULL)
    {
        printf("%d\n", P->nbr);
        P = P->svt;
    }
    printf("\n");
}

int main()
{

    Pile Mapile;
    Mapile.first = NULL;
    int N, val;
    printf("entrez le max de valeurs que peut contenir la pile:\n");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &val);
        empiler(&Mapile, val);
    }
     printf("les valeurs de la pile sont:\n");
    afficher(&Mapile);

    return 0;
}
