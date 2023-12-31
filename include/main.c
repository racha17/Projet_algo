#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"
#include "structure.h"
#include "F_predefinies.h"
#include "Fonctions.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define MAX_BUTTONS 3

// Constants for button dimensions
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

typedef struct Button
{
    Rectangle rect;
    Color color;
    const char *text;
    bool pressed;
} Button;

void DrawPile(Pile *pile, bool drawEmptyPile)
{

    if (drawEmptyPile)
    {
        // Draw an empty rectangle to represent the empty pile
        DrawRectangleLinesEx((Rectangle){500, 500, 150, 70}, 2, DARKGRAY);
    }
    else
    {
        // Draw the elements of the pile
        int yOffset = 200;
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

        // Restore the original pile in the correct order
        while (!Pilevide(&pile1))
        {
            empiler(pile, depiler(&pile1));
        }
    }
}

int main(void)
{

    // Pile Mapile = initPile();
    // int N, val;

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

    //}

    // Initialiser la fenêtre
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");

    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "insert", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "remove", false}};

    Pile myPile = initPile();
    bool drawEmptyPile = false;

    char inputText[256] = "";

    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_BUTTONS; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
            {
                buttons[i].color = BEIGE;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    buttons[i].pressed = true;

                    if (i == 0)
                    {
                        myPile = initPile();
                        drawEmptyPile = true;
                        printf("Pile created!\n");
                    }
                    else if (i == 1)
                    {
                        // Use strtol for better error handling
                        char *endptr;
                        int value = (int)strtol(inputText, &endptr, 10);

                        if (*endptr == '\0')
                        {
                            empiler(&myPile, value);
                            drawEmptyPile = false;
                            printf("Value inserted: %d\n", value);
                        }
                        memset(inputText, 0, sizeof(inputText));
                    }
                    else if (i == 2)
                    {
                        char *endptr;
                        int value = (int)strtol(inputText, &endptr, 10);
                        if (*endptr == '\0')
                        {
                            suppression(&myPile, value);
                            drawEmptyPile = false;
                            printf("Value removed: %d\n", value);
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
            int value = (int)strtol(inputText, &endptr, 10);

            if (*endptr == '\0')
            {
                empiler(&myPile, value);
                drawEmptyPile = false;
                printf("Value inserted: %d\n", value);
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

        DrawPile(&myPile, drawEmptyPile);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}