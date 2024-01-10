#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"
int main{
  // Initialiser la fenêtre
    // Pile Mapile = initPile();
    //  int k, N, val , valeur , val2;
    //    char choix;
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
    // printf("l'etat de la pile apres suppression:\n");
    // afficher(&Mapile);

    //       // test INSERTION
    //      printf ("voulez-vous entrer une valeur O/N ?:\n");
    //  scanf ("%c",&choix);
    // if (choix=='O'||choix=='o'){
   //    /*demander à l'utilisateur d'entrer une valeur et la position*/
   //  printf ("donnez une valeur à ajouter:\n");
   // scanf ("%d",&valeur);
   // printf ("donnez une position");
   // scanf ("%d",&k);
   //  } else {
        /*choisir une valeur aléatoire et une position aléatoire*/
        
   //     valeur = rand() %100; /*valeurs entre 0 et 99*/
   //     k = rand() %100;
   //   }

 //   /*inserer la valeur dans la pile*/
 //    insertion(&mapile,valeur,k);
 //   /*affichage*/
 //   printf ("Etat de la pile aprés insertion :\n");
 //   afficherPile(&mapile);



    /* printf("veuillez donner la valeur que vous voulez rechercher ");
scanf("%d",&val2);

if (recherche(&Mapile,val2)==false)
{
    printf("la valeur n'existe pas. \n ");

}
else printf("la valeur existe . \n");


     */

    //   return 0;

    //}
/* UTILISATION DES PILES DANS
L’EVALUATION DES EXPRESSIONS
ARITHMETIQUES */
// une petite explication 
/* Une utilisation courante des piles est l’élaboration par le
compilateur d’une forme intermédiaire de l’expression à évaluer.
Après l’analyse lexicale et syntaxique, l’expression est traduite en
une forme intermédiaire plus facilement évaluable
Soit l’expression : A + B. Son évaluation ne peut être faite
immédiatement lors de la rencontre d’un opérateur car le 2ème
opérande n’est pas encore connu par la machine. Par contre si
l’expression pouvait être écrite sous la forme AB+ alors elle serait
directement évaluable car les deux opérandes sont connus avant
l’opérateur.
La notation < Opérande> < Opérateur> < Opérande> est dite
INFIXE.
L’autre représentation plus facilement évaluable est dite POSTFIXE
ou POLONAISE SUFFIXE. Elle a la forme :
< Opérande Gauche > < Opérande Droit > < Opérateur> */


#define MAX_TAILLE_EXPRESSION 100

// Définition des fonctions pour manipuler les piles
typedef struct {
    char items[MAX_TAILLE_EXPRESSION];
    int top;
} Pile2;

void initPile2(Pile2 *pile) {
    pile->top = -1;
}

int pileVide2(Pile2 *pile) {
    return pile->top == -1;
}

int pilePleine2(Pile2 *pile) {
    return pile->top == MAX_TAILLE_EXPRESSION - 1;
}

void empiler2(Pile2 *pile, char element) {
    if (!pilePleine2(pile)) {
        pile->items[++pile->top] = element;
    } else {
        printf("Erreur : la pile est pleine.\n");
        exit(EXIT_FAILURE);
    }
}

char depiler2(Pile2 *pile) {
    if (!pileVide2(pile)) {
        return pile->items[pile->top--];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

char sommetPile2(Pile2 *pile) {
    if (!pileVide2(pile)) {
        return pile->items[pile->top];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour vérifier si un caractère est un opérande
int estOperande(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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
        return 0;  // Pour les autres caractères (parenthèses, etc.)
    }
}

// Algorithme de transformation
void transformerExpression(char *expression) {
    Pile2 pileP, pileR;
    char x;

    initPile2(&pileP);
    initPile2(&pileR);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (estOperande(expression[i])) {
            empiler2(&pileR, expression[i]);
        } else if (expression[i] == '(') {
            empiler2(&pileP, expression[i]);
        } else if (estOperateur(expression[i])) {
            while (!pileVide2(&pileP) && estOperateur(sommetPile2(&pileP)) &&
                   (priorite(expression[i]) <= priorite(sommetPile2(&pileP)))) {
                x = depiler2(&pileP);
                empiler2(&pileR, x);
            }
            empiler2(&pileP, expression[i]);
        } else if (expression[i] == ')') {
            while (!pileVide2(&pileP) && sommetPile2(&pileP) != '(') {
                x = depiler2(&pileP);
                empiler2(&pileR, x);
            }
            depiler2(&pileP); // Dépiler la parenthèse ouvrante
        }
    }

    while (!pileVide2(&pileR)) {
        x = depiler2(&pileR);
        empiler2(&pileP, x);
    }

    while (!pileVide2(&pileP)) {
        x = depiler2(&pileP);
        printf("%c ", x);
    }
}

int main() {
    char expression[MAX_TAILLE_EXPRESSION];

    printf("Entrez une expression infixée : ");
    fgets(expression, sizeof(expression), stdin);

    printf("L'expression postfixée est : ");
    transformerExpression(expression);

    return 0;
}

