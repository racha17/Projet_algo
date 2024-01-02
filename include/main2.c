#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"


#define MAX_TAILLE_EXPRESSION 100

// Définition des fonctions pour manipuler les piles
typedef struct {
    char items[MAX_TAILLE_EXPRESSION];
    int top;
} Pile;

void initPile(Pile *pile) {
    pile->top = -1;
}

int pileVide(Pile *pile) {
    return pile->top == -1;
}

int pilePleine(Pile *pile) {
    return pile->top == MAX_TAILLE_EXPRESSION - 1;
}

void empiler(Pile *pile, char element) {
    if (!pilePleine(pile)) {
        pile->items[++pile->top] = element;
    } else {
        printf("Erreur : la pile est pleine.\n");
        exit(EXIT_FAILURE);
    }
}

char depiler(Pile *pile) {
    if (!pileVide(pile)) {
        return pile->items[pile->top--];
    } else {
        printf("Erreur : la pile est vide.\n");
        exit(EXIT_FAILURE);
    }
}

char sommetPile(Pile *pile) {
    if (!pileVide(pile)) {
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
    Pile pileP, pileR;
    char x;

    initPile(&pileP);
    initPile(&pileR);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (estOperande(expression[i])) {
            empiler(&pileR, expression[i]);
        } else if (expression[i] == '(') {
            empiler(&pileP, expression[i]);
        } else if (estOperateur(expression[i])) {
            while (!pileVide(&pileP) && estOperateur(sommetPile(&pileP)) &&
                   (priorite(expression[i]) <= priorite(sommetPile(&pileP)))) {
                x = depiler(&pileP);
                empiler(&pileR, x);
            }
            empiler(&pileP, expression[i]);
        } else if (expression[i] == ')') {
            while (!pileVide(&pileP) && sommetPile(&pileP) != '(') {
                x = depiler(&pileP);
                empiler(&pileR, x);
            }
            depiler(&pileP); // Dépiler la parenthèse ouvrante
        }
    }

    while (!pileVide(&pileR)) {
        x = depiler(&pileR);
        empiler(&pileP, x);
    }

    while (!pileVide(&pileP)) {
        x = depiler(&pileP);
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

