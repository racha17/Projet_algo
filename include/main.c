#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"


int main()
{

    // Pile Mapile = initPile();
     int N, val , valeur ;
       char choix;
    // printf("entrez le max de valeurs que peut contenir la pile:\n");
    // scanf("%d", &N);

    // for (int i = 0; i < N; i++)
    // {
    //     scanf("%d", &val);
    //     empiler(&Mapile, val);
    // }
    // printf("les valeurs de la pile sont:\n");
    // afficher(&Mapile);

    // printf("donnez la valeur que vous voulez supprimer:\n");
    // scanf("%d", &val);

    // suppression(&Mapile, val);
    // afficher(&Mapile);

    // printf("veuillez donner la valeur que vous voulez rechercher:\n");
    // scanf("%d", &val);
    // if (recherche(&Mapile, val) == false)
    // {
    //     printf("la valeur existe n'existe pas\n ");
    // }
    // else
    // {
    //     printf("la valeur existe . \n");
    // }
    
   // INSERTION 
    printf ("voulez-vous entrer une valeur O/N ?:\n");
    scanf ("%c",&choix);
    if (choix=='O'||choix=='o'){
        /*demander à l'utilisateur d'entrer une valeur*/
    printf ("donnez une valeur à ajouter:\n");
    scanf ("%d",&valeur);
    } else {
        /*choisir une valeur aléatoire*/
        
        valeur = rand() %100; /*valeurs entre 0 et 99*/
    }
    /*inserer la valeur dans la pile*/
    insertion(&Mapile,valeur);
    /*affichage*/
    printf ("Etat de la pile aprés insertion :\n");
    afficherPile(&Mapile);

  return 0;
}
