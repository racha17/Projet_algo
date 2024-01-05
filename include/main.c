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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");

    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "insert", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "remove", false}};

    Pile MaPile = initPile();
    Pile pile2 = initPile();

    bool supressed = true;
    int tosupress = -1;
    bool supAnimation = false;

    char inputText[256] = "";

    float animationProgress = 0.0f;
    float animationProgressThreshold = 0.5f;

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
                        memset(inputText, 0, sizeof(inputText));
                    }
                    else if (i == 2 && tosupress == -1)
                    {
                        supressed = false;
                        char *endptr;
                        tosupress = (int)strtol(inputText, &endptr, 10);
                        animationProgress = 0.0f;
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

                printf("val inserted: %d\n", val);
            }
            memset(inputText, 0, sizeof(inputText));
        }
        if (IsKeyPressed(KEY_RIGHT) && (tosupress != -1) && !supAnimation)
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
        if (supAnimation)
        {

            if (animationProgress >= 0.0f && animationProgress <= animationProgressThreshold)
            {

                DrawRectangleRec((Rectangle){500, 200 - 1000 * animationProgress, 180, 60}, RED);
                DrawText(TextFormat("%d", tosupress), 520, 202 - 1000 * animationProgress, 50, BEIGE);

                animationProgress += 0.001f;
            }
            else
            {
                supAnimation = false;
                supressed = true;
            }
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

        DrawPile(&MaPile, &pile2);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}