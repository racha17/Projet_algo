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
#define MAX_BUTTONS 3
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

typedef struct Button
{
    Rectangle rect;
    Color color;
    const char *text;
    int pressed;
} Button;

void DrawPile(Pile *pile, Pile *pile2, bool drawPilevide)
{
    int yOffset;

    // Draw the first pile
    if (drawPilevide)
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
            DrawRectangleRec((Rectangle){700, yOffset, 180, 60}, RED);
            DrawText(TextFormat("%d", val), 720, yOffset + 2, 20, WHITE);
            yOffset += 65;
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile2, depiler(&pile1));
        }
    }
}

int main()
{

    // Pile Mapile = initPile();
    //  int N, val , valeur ;
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

    //       // INSERTION
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

    //   return 0;

    //}

    // Initialiser la fenêtre
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");

    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "insert", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "remove", false}};

    Pile MaPile = initPile();

    Pile pile2 = initPile();

    bool drawPilevide = false;

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
                        drawPilevide = true;
                        printf("Pile a ete cree!\n");
                    }
                    else if (i == 1)
                    {

                        char *endptr;
                        int val = (int)strtol(inputText, &endptr, 10);

                        if (*endptr == '\0')
                        {
                            empiler(&MaPile, val);
                            drawPilevide = false;
                            printf("Valeur inseree %d\n", val);
                        }
                        memset(inputText, 0, sizeof(inputText));
                    }
                    else if (i == 2)
                    {
                        char *endptr;
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
                }
            }
            else
            {
                buttons[i].color = DARKBROWN;
                buttons[i].pressed = false;
            }

            // Draw the button
            DrawRectangleRec(buttons[i].rect, buttons[i].color);
            DrawText(buttons[i].text, buttons[i].rect.x + 10, buttons[i].rect.y + 10, 20, BLACK);
        }

        Rectangle inputBox = {50, 300, 150, 30};
        DrawRectangleRec(inputBox, BROWN);

        if (IsKeyPressed(KEY_ENTER))
        {
            char *endptr;
            int val = (int)strtol(inputText, &endptr, 10);

            if (*endptr == '\0')
            {
                empiler(&MaPile, val);
                drawPilevide = false;
                printf("val inserted: %d\n", val);
            }
            memset(inputText, 0, sizeof(inputText));
        }

        int key = GetKeyPressed();
        if (key != 0)
        {
            int length = strlen(inputText);
            if (length < sizeof(inputText) - 1)
            {
                inputText[length] = (char)key;
                inputText[length + 1] = '\0';
            }
        }

        BeginDrawing();
        ClearBackground(BEIGE);

        DrawText(inputText, inputBox.x + 5, inputBox.y + 5, 20, BEIGE);

        DrawPile(&MaPile, &pile2, drawPilevide);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
