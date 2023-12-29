#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct element element;
struct element
{
    int nombre;
    element *suivant;

};
typedef struct pile pile;
struct pile 
{
    element *premier;


};
void initialiserpile (pile *pile){
      pile->premier = -1;

}
void empiler(pile *pile,int nvnombre)
{

    element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvnombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

int depiler(pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return nombreDepile;
}
void afficherPile(pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    element *actuel = pile->premier;

    while (actuel != NULL)
    {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");
}
int main (){
    pile mapile;
    int valeur;
    char choix;
    int n;
    int valpile;
    initialiserpile(&mapile);
    /*création de la pile*/
    printf ("donnez le max d'elements que la pile peut contenir :\n");
    scanf ("%d",&n);
    for (int i=1;i<=n;i++)
    {
        printf ("veuillez entrer la valeur numero %d :\n",i);
        scanf ("%d",&valpile);
        empiler(&mapile,valpile);
    }
    printf ("Etat de la pile :\n");
    afficherPile(&mapile);
    /*insertion*/
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
    /*empiler la valeur dans la pile*/
    empiler(&mapile,valeur);
    /*affichage*/
    printf ("Etat de la pile :\n");
    afficherPile(&mapile);

  return 0;
}











