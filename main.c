#include <stdio.h>
#include <stdlib.h>

typedef struct list list struct list
{
    int nbr;
    struct list *svt;
};
typedef struct pile pile struct pile
{
    list *first;
};

void empiler(pile *pile, int val)
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

int main()
{
}