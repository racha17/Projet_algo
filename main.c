#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list
{
    int nbr;
    struct list *svt;
} list;

typedef struct Pile{
list *first;
}Pile;

Pile initPile()
{
    Pile *p=malloc(sizeof(Pile));
    p->first=NULL;
    return *p  ;
}

bool Pilevide(Pile *pile)
{
    return pile->first==NULL;
}

int SommetPile(Pile *pile)
{
    if(Pilevide(pile)){
        exit(EXIT_FAILURE);
    }
    return pile->first->nbr;

}

void empiler(Pile *pile, int val)
{

    list *L = malloc(sizeof(list));
    if (L==NULL)
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

void afficher(Pile *pile)
{
    int val;
    if (Pilevide(pile))
    {
        printf("la pile est vide\n");
        exit(EXIT_FAILURE);
    }

    Pile pile1=initPile();

    while(!Pilevide(pile)){
        val=depiler(pile);
        printf("%d\n",val);
        empiler(&pile1,val);
    }
    while(!Pilevide(&pile1)){
        empiler(pile,depiler(&pile1));
    }

    printf("\n");
}

int main()
{

    Pile Mapile=initPile();
    int N,val;

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


