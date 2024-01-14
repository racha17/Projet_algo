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
#define MAX_BUTTONS 6
#define BUTTON_WIDTH 280
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
    if (Pilevide(pile))
    {
        DrawRectangleLinesEx((Rectangle){500, 300, 150, 70}, 2, DARKPURPLE);
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
            DrawRectangleRec((Rectangle){500, yOffset, 180, 60}, DARKPURPLE);
            DrawText(TextFormat("%d", val), 520, yOffset + 2, 50, SKYBLUE);
            yOffset += 65;
        }
        while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }
    }
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
            DrawText(TextFormat("%d", val), 720, yOffset + 4, 60, LIGHTGRAY);
            yOffset += 65;
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile2, depiler(&pile1));
        }
    }
}

int LongueurPile(Pile *pile)
{
    int longueur = 1;
    int x;
    Pile longPile = initPile();
    while (!Pilevide(pile))
    {
        x = depiler(pile);
        empiler(&longPile, x);
        longueur = longueur + 1;
    }
    while (!Pilevide(&longPile))
    {
        x = depiler(&longPile);
        empiler(pile, x);
    }
    return longueur;
}
void DrawPileRECHERCHE(Pile *pile, Pile *pile2, bool drawPilevide, int valeurRecherchee, int trouve)
{
    int yOffset;

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

            // Nouvelle logique pour la couleur de fond pendant la recherche
            if (trouve == 1 && val == valeurRecherchee)
            {
                DrawRectangleRec((Rectangle){500, yOffset, 180, 60}, GREEN);
            }
            else
            {
                DrawRectangleRec((Rectangle){500, yOffset, 180, 60}, RED);
            }

            DrawText(TextFormat("%d", val), 520, yOffset + 2, 50, BEIGE);
            yOffset += 65;
        }

        while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }
    }
}
void DrawRecherche(int trouve)
{
    if (trouve == 1)
    {
        DrawText("La valeur a été trouvée ", 900, 200, 20, BLACK);
    }
    else if (trouve == 2)
    {
        DrawText("La valeur n'a pas été trouvée ", 890, 200, 20, BLACK);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");
    InitAudioDevice();
    Music music = LoadMusicStream("recherchevoice.mp3");
    music.looping = false;
    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "Create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "FillStack", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "Remove", false},
        {{50, 260, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "InsertElement", false},
        {{50, 330, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "search", false},
        {{50, 400, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKPURPLE, "Transformation algorithm", false}};

    Pile MaPile = initPile();
    Pile pile2 = initPile();

    int insertionValue = 0;
    int insertionPosition = -1;

    int nbrpos = 0;

    bool insertedvalue = false;
    bool inserted = true;

    bool supressed = true;
    int tosupress = -1;
    bool supAnimation = false;

    int stringSize = 256;
    char *inputText = (char *)calloc(stringSize, sizeof(char));

    float animationProgress = 0.0f;
    float animationProgressThreshold = 0.5f;
    int trouve = 0;
    bool showExplanation = false;
    int valeurRecherchee;
    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_BUTTONS; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
            {
                buttons[i].color = SKYBLUE;
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
                    }
                    else if (i == 3)
                    {
                        inserted = false;
                        char *endptr;
                        if (insertionPosition == -1 && insertedvalue)
                        {
                            insertionPosition = (int)strtol(inputText, &endptr, 10);
                            printf("la position est :%d\n", insertionPosition);
                            nbrpos = LongueurPile(&MaPile) - insertionPosition;
                        }

                        if (!insertedvalue)
                        {
                            insertionValue = (int)strtol(inputText, &endptr, 10);
                            printf("la valeur a inserer est:%d\n", insertionValue);
                            insertedvalue = true;
                        }
                    }
                    else if (i == 4)
                    {
                        char *endptr;
                        int val = (int)strtol(inputText, &endptr, 10);
                        valeurRecherchee = val;
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

                        inputText = (char *)calloc(stringSize, sizeof(char));
                    }
                    else if (i == 5)
                    {
                        showExplanation = true;
                    }
                }
            }

            {
                buttons[i].color = DARKPURPLE;
                buttons[i].pressed = false;
            }

            DrawRectangleRec(buttons[i].rect, buttons[i].color);
            DrawText(buttons[i].text, buttons[i].rect.x + 10, buttons[i].rect.y + 10, 20, BLACK);
        }

        Rectangle inputBox = {50, 500, 150, 30};
        DrawRectangleRec(inputBox, DARKPURPLE);

        if (IsKeyPressed(KEY_RIGHT))
        {
            if ((tosupress != -1) && !supAnimation)
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
                            printf("la valeur %d a ete supprimee.\n", tosupress);
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
                    }
                }
            }
            else if (insertedvalue && insertionPosition != -1)
            {

                int x;
                if (!inserted)
                {
                    if (!Pilevide(&MaPile))
                    {

                        if (nbrpos != 0)
                        {
                            x = depiler(&MaPile);
                            empiler(&pile2, x);
                            nbrpos = nbrpos - 1;
                        }
                        else
                        {
                            empiler(&MaPile, insertionValue);
                            inserted = true;
                        }
                    }
                    else
                    {
                        if (nbrpos == 0)
                        {
                            empiler(&MaPile, insertionValue);
                        }
                        inserted = true;
                    }
                }
                else
                {
                    if (!Pilevide(&pile2))
                    {
                        x = depiler(&pile2);
                        empiler(&MaPile, x);
                    }
                    if (Pilevide(&pile2))

                    {
                        insertionPosition = -1;
                        insertedvalue = false;
                    }
                }
            }
        }
        if (insertionPosition == -1 && !inserted)
        {
            if (!insertedvalue)
            {
                DrawText("Entrez la valeur que vous voulez inserer:", 50, 600, 20, BLACK);
            }
            else
            {

                DrawText("A quelle position voulez vous l'inserer:", 50, 600, 20, BLACK);
            }
        }

        if ((!supressed && tosupress != -1) || (!inserted && insertionPosition != -1))
        {
            DrawText("Press Right Key :", 58, 600, 20, BLACK);
        }

        if (Pilevide(&MaPile))
        {
            if (!supressed)
            {
                DrawText("Oops! La valeur n'existe pas dans la pile.\n\nEntrez une autre valeur!", 58, 550, 20, BLACK);
            }
        }

        if (supressed && !Pilevide(&pile2) && !Pilevide(&MaPile) && insertionPosition == -1)
        {

            DrawText("YAY! Votre valeur a été supprimée!", 58, 650, 20, BLACK);
        }

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
        ClearBackground(LIGHTGRAY);
        DrawText(inputText, inputBox.x + 5, inputBox.y + 5, 20, SKYBLUE);
        DrawPile(&MaPile, &pile2);
        DrawRecherche(trouve);
        if (trouve == 1)
        {

            DrawPileRECHERCHE(&MaPile, &pile2, true, valeurRecherchee, trouve);
            UpdateMusicStream(music);
        }
        if (showExplanation)
        {
            DrawText("Une utilisation courante des piles est l'élaboration par le compilateur\n"
                     "d'une forme intermédiaire de l'expression à évaluer.\n"
                     "Après l'analyse lexicale et syntaxique, l'expression est traduite en\n"
                     "une forme intermédiaire plus facilement évaluable.\n"
                     "Soit l'expression : A + B. Son évaluation ne peut être faite\n"
                     "immédiatement lors de la rencontre d'un opérateur car le 2ème\n"
                     "opérande n'est pas encore connu par la machine. Par contre si\n"
                     "l'expression pouvait être écrite sous la forme AB+ alors elle serait\n"
                     "directement évaluable car les deux opérandes sont connus avant\n"
                     "l'opérateur.\n"
                     "La notation < Opérande> < Opérateur> < Opérande> est dite\n"
                     "INFIXE.\n"
                     "L'autre représentation plus facilement évaluable est dite POSTFIXE\n"
                     "ou POLONAISE SUFFIXE. Elle a la forme :\n"
                     "< Opérande Gauche > < Opérande Droit > < Opérateur>",
                     600, 550, 18, DARKPURPLE);
        }
        EndDrawing();
    }
    UnloadMusicStream(music); // Unload music stream buffers from RAM

    CloseAudioDevice(); // Close audio device (music streaming is automatically stopped)
    CloseWindow();
    free(inputText);
    return 0;
}
