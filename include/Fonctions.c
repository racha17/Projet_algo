#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
#include "F_predefinies.h"
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
bool suppression(Pile *pile, int val)
{

    Pile pile1;
    pile1.first = NULL;
    int x;
    bool trouve = false;
    while (!Pilevide(pile))
    {
        x = depiler(pile);
        if (x != val)
        {
            empiler(&pile1, x);
        }
        else
        {
            trouve = true;
        }
    }
    while (!Pilevide(&pile1))
    {
        empiler(pile, depiler(&pile1));
    }
    return trouve;
}
void insertion (Pile *pile,int val,int k)
{    Pile R;
    int x;
    if (Pilevide(&pile)){
    empiler (&pile,val);
    }
    else if (k==1){
    empiler(&pile,val);
    }

    else {
        initPile(&R);
        while (!Pilevide(&pile) && k>1){
            depiler2(&pile,x);
            empiler(&R,x);
            k=k-1;
        }
    }
    if (k==1){
        empiler(&pile,val);
    }else, { printf ("erreur!!!");}
    while (!Pilevide(&pile)){
            depiler2 (&R,x);
            empiler (&pile,x);
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
// Algorithme de transformation
void transformerExpression(char *expression)
{
    Pile pileP, pileR;
    char x;

    initPile(&pileP);
    initPile(&pileR);

    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (estOperande(expression[i]))
        {
            empiler(&pileR, expression[i]);
        }
        else if (expression[i] == '(')
        {
            empiler(&pileP, expression[i]);
        }
        else if (estOperateur(expression[i]))
        {
            while (!pileVide(&pileP) && estOperateur(sommetPile(&pileP)) &&
                   (priorite(expression[i]) <= priorite(sommetPile(&pileP))))
            {
                x = depiler(&pileP);
                empiler(&pileR, x);
            }
            empiler(&pileP, expression[i]);
        }
        else if (expression[i] == ')')
        {
            while (!pileVide(&pileP) && sommetPile(&pileP) != '(')
            {
                x = depiler(&pileP);
                empiler(&pileR, x);
            }
            depiler(&pileP); // Dépiler la parenthèse ouvrante
        }
    }

    while (!pileVide(&pileR))
    {
        x = depiler(&pileR);
        empiler(&pileP, x);
    }

    while (!pileVide(&pileP))
    {
        x = depiler(&pileP);
        printf("%c ", x);
    }
}
