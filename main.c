#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"
#include "F_predefenies.h"
#include "Fonctions.h"

int main()
{

    Pile Mapile = initPile();
    int N, val, val2;

    printf("entrez le max de valeurs que peut contenir la pile:\n");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &val);
        empiler(&Mapile, val);
    }
    printf("les valeurs de la pile sont:\n");
    afficher(&Mapile);

    printf("donnez la valeur que vous voulez supprimer:\n");
    scanf("%d", &val);

    suppression(&Mapile, val);
    afficher(&Mapile);
    return 0;
    printf("veuillez donner la valeur que vous voulez rechercher ");
scanf("%d",&val2);

if (recherche(&Mapile,val)==false)
{
    printf("la valeur n'existe pas. \n ");

}
else printf("la valeur existe . \n");

}

}
