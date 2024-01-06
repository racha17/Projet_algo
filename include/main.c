#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAX_BUTTONS 5
#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 50
typedef struct Button
{
    Rectangle rect;
    Color color;
    const char *text;
    int pressed;
} Button;

void DrawPile(Pile *pile, Pile *pile2)
{
    int yOffset;

    // Draw the first pile
    if (Pilevide(pile))
    {
        DrawRectangleLinesEx((Rectangle){500, 500, 150, 70}, 2, DARKGRAY);
    }
    else
    {
        yOffset = 200;
        int val;
        Pile pile1 = initPile();
        while (!Pilevide(pile))
        {
            val = depiler(pile);
            empiler(&pile1, val);
            DrawRectangleRec((Rectangle){500, yOffset, 180, 60}, BROWN);
            DrawText(TextFormat("%d", val), 520, yOffset + 2, 50, BEIGE);
            yOffset += 65;
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }
    }

    // Draw the second pile
    yOffset = 200;
    if (!Pilevide(pile2))
    {
        int val;
        Pile pile1 = initPile();

        while (!Pilevide(pile2))
        {
            val = depiler(pile2);
            empiler(&pile1, val);
            DrawRectangleRec((Rectangle){700, yOffset, 180, 60}, YELLOW);
            DrawText(TextFormat("%d", val), 720, yOffset + 4, 60, BEIGE);
            yOffset += 65;
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile2, depiler(&pile1));
        }
    }
}
void DrawRecherche(int trouve)
{
    if (trouve == 1)
    {
        DrawText("la valeur a ete trouve ", 900, 200, 20, WHITE);
    }
    else if (trouve == 2)
    {
        DrawText("la valeur n'a pas ete trouve ", 890, 200, 20, WHITE);
    }
}

int main()
{

    // Initialiser la fenêtre
    // Pile Mapile = initPile();
    //  int N, val , valeur , val2;
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
    //     printf ("voulez-vous entrer une valeur O/N ?:\n");
    //     scanf ("%c",&choix);
    //     if (choix=='O'||choix=='o'){
    //         /*demander à l'utilisateur d'entrer une valeur*/
    //     printf ("donnez une valeur à ajouter:\n");
    //     scanf ("%d",&valeur);
    //     } else {
    //         /*choisir une valeur aléatoire*/

    //         valeur = rand() %100; /*valeurs entre 0 et 99*/
    //     }
    //     /*inserer la valeur dans la pile*/
    //     insertion(&Mapile,valeur);
    //     /*affichage*/
    //     printf ("Etat de la pile aprés insertion :\n");
    //     afficherPile(&Mapile);
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

    // Initialiser la fenêtre
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");

    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "insert", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "remove", false},
        {{50, 260, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "search", false},
        {{50, 330, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "Transformation algorithm", false}};

    Pile MaPile = initPile();
    Pile pile2 = initPile();

    bool supressed = true;
    int tosupress = -1;
    bool supAnimation = false;

    int stringSize = 256;
    char *inputText = (char *)calloc(stringSize, sizeof(char));

    float animationProgress = 0.0f;
    float animationProgressThreshold = 0.5f;
    bool drawPilevide = false;
    int trouve = 0;

    bool showExplanation = false;
    char inputText[256] = "";

    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_BUTTONS; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
            {
                buttons[i].color = BROWN;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    buttons[i].pressed = true;

                    if (i == 0)
                    {
                        MaPile = initPile();

                        printf("Pile a ete cree!\n");
                    }
                    else if (i == 1)
                    {
                        char *endptr;
                        int val = (int)strtol(inputText, &endptr, 10);

                        if (*endptr == '\0')
                        {
                            empiler(&MaPile, val);

                            printf("Valeur inseree %d\n", val);
                        }
                        inputText = (char *)calloc(stringSize, sizeof(char));
                    }
                    else if (i == 2 && tosupress == -1)
                    {
                        supressed = false;
                        char *endptr;
                        tosupress = (int)strtol(inputText, &endptr, 10);
                        animationProgress = 0.0f;
                        int val = (int)strtol(inputText, &endptr, 10);
                        if (*endptr == '\0')
                        {
                            if (suppression(&MaPile, val))
                            {
                                empiler(&pile2, val);
                                drawPilevide = false;
                                printf("Valeur supprimee: %d\n", val);
                            }
                            else
                            {
                                printf("la valeur %d n'existe pas dans la pile.\n", val);
                            }
                        }

                        memset(inputText, 0, sizeof(inputText));
                    }
                    else if (i == 3)
                    {
                        char *endptr;
                        int val = (int)strtol(inputText, &endptr, 10);

                        if (*endptr == '\0')
                        {
                            if (recherche(&MaPile, val))
                            {
                                printf("La valeur %d a été trouvée dans la pile.\n", val);
                                trouve = 1;
                            }
                            else
                            {
                                printf("La valeur %d n'existe pas dans la pile.\n", val);
                                trouve = 2;
                            }
                        }

                        memset(inputText, 0, sizeof(inputText));
                    }
                    else if (i == 4)
                    {

                        showExplanation = true;
                    }
                }
            }
            else
            {
                buttons[i].color = DARKBROWN;
                buttons[i].pressed = false;
            }
            DrawRectangleRec(buttons[i].rect, buttons[i].color);
            DrawText(buttons[i].text, buttons[i].rect.x + 10, buttons[i].rect.y + 10, 20, BLACK);
        }
        if (buttons[2].pressed)
        {
            DrawText("Press Right Key to Suppress:", 58, 400, 20, BROWN);
        }

        Rectangle inputBox = {50, 400, 150, 30};
        DrawRectangleRec(inputBox, BROWN);

        if (IsKeyPressed(KEY_RIGHT) && (tosupress != -1) && !supAnimation)
            /*    if (IsKeyPressed(KEY_ENTER))
                {
                    int x;
                    if (!supressed)
                    {
                        if (!Pilevide(&MaPile))
                        {
                            x = depiler(&MaPile);
                            if (x != tosupress)
                            {
                                empiler(&pile2, x);
                            }
                            else
                            {
                                supAnimation = true;
                            }
                        }
                        else
                        {
                            supressed = true;
                        }
                    }
                    else
                    {
                        if (!Pilevide(&pile2))
                        {
                            x = depiler(&pile2);
                            empiler(&MaPile, x);
                        }
                        else
                        {
                            tosupress = -1;
                            // supressed = true;
                        }
                    }
                }
                if (Pilevide(&MaPile) && supressed == false)
                {
                    DrawText("Oops  ! la valeur n'existe pas dans la pile.\n\nEntrez une autre valeur!", 58, 500, 20, BROWN);
                }
                    memset(inputText, 0, sizeof(inputText));
                }*/

            if (supAnimation)
            {

                if (animationProgress >= 0.0f && animationProgress <= animationProgressThreshold)
                {

                    DrawRectangleRec((Rectangle){500, 200 - 1000 * animationProgress, 180, 60}, RED);
                    DrawText(TextFormat("%d", tosupress), 520, 202 - 1000 * animationProgress, 50, BLACK);

                    animationProgress += 0.001f;
                }
                else
                {
                    supAnimation = false;
                    supressed = true;
                }
            }
        int key = GetKeyPressed();
        if ((key >= 48 && key <= 57) || (key == 259 || key == 261))
        {
            int length = strlen(inputText);
            if (length < sizeof(inputText) - 1)
            {
                inputText[length] = (char)key;
                inputText[length + 1] = '\0';
            }
            if (length > 0 && (key == 259 || key == 261))
            {
                inputText[length - 1] = '\0';
            }
        }

        BeginDrawing();
        ClearBackground(BEIGE);

        DrawText(inputText, inputBox.x + 5, inputBox.y + 5, 20, BEIGE);

        DrawPile(&MaPile, &pile2);

        DrawPile(&MaPile, &pile2, drawPilevide);

        DrawRecherche(trouve);
        if (showExplanation)
        {

            {
                DrawText("Une utilisation courante des piles est l'elaboration par le compilateur\n"
                         "d'une forme intermediaire de l'expression a evaluer.\n"
                         "Apres l'analyse lexicale et syntaxique, l'expression est traduite en\n"
                         "une forme intermediaire plus facilement evaluable.\n"
                         "Soit l'expression : A + B. Son evaluation ne peut etre faite\n"
                         "immediatement lors de la rencontre d'un operateur car le 2eme\n"
                         "operande n'est pas encore connu par la machine. Par contre si\n"
                         "l'expression pouvait etre ecrite sous la forme AB+ alors elle serait\n"
                         "directement evaluable car les deux operandes sont connus avant\n"
                         "l'operateur.\n"
                         "La notation < Operande> < Operateur> < Operande> est dite\n"
                         "INFIXE.\n"
                         "L'autre representation plus facilement evaluable est dite POSTFIXE\n"
                         "ou POLONAISE SUFFIXE. Elle a la forme :\n"
                         "< Operande Gauche > < Operande Droit > < Operateur>",
                         400, 100, 18, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}