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
#define MAX_BUTTONS 4
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
//*********************************************************************
typedef struct InsertionButton
{
    Rectangle rect;
    Color color;
    const char *text;
    bool pressed;
} InsertionButton;

void DrawInsertionButtons(InsertionButton *insertionButtons, int numButtons)
{
    for (int i = 0; i < numButtons; i++)
    {
        DrawRectangleRec(insertionButtons[i].rect, insertionButtons[i].color);
        DrawText(insertionButtons[i].text, insertionButtons[i].rect.x + 10, insertionButtons[i].rect.y + 10, 20, BLACK);
    }
}
void HandleInsertion(Pile *pile, int val, int k)
{
     Pile R;
    int x;

    if (Pilevide(pile) || k <= 0)
    {
        empiler(pile, val);
        return;
    }

    initPile(&R);
    while (!Pilevide(pile) && k > 1)
    {
        depiler2(pile, &x);
        empiler(&R, x);
        k = k - 1;
    }

    if (k == 1)
    {
        empiler(pile, val);
    }
    else
    {
        printf("Erreur!!!\n");
    }

    while (!Pilevide(&R))
    {
        depiler2(&R, &x);
        empiler(pile, x);
    }
}
int GetInputPosition()
{
    int position;
    printf("Enter position: ");
    scanf("%d", &position);
    return position;
}
int GetInputValue()
{
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    return value;
}
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project");
    Button buttons[MAX_BUTTONS] = {
        {{50, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "create", false},
        {{50, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "insert", false},
        {{50, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "remove", false},
    };
//****************************************************************************************
    InsertionButton insertionButtons[] = {
        {{200, 50, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "Enter Value", false},
        {{200, 120, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "Enter Position", false},
        {{200, 190, BUTTON_WIDTH, BUTTON_HEIGHT}, DARKBROWN, "Perform Insertion", false},
    };
//***************************************************************************************
    

    Pile MaPile = initPile();
    Pile pile2 = initPile();
//*****************************************************************************************
     int GetInputPosition();
    int GetInputValue();

    int insertionValue = 0;
    int insertionPosition = 0;
    bool showInsertionButtons = false;

//*****************************************************************************************
    bool supressed = true;

    int tosupress = -1;
    bool supAnimation = false;

    int stringSize = 256;
    char *inputText = (char *)calloc(stringSize, sizeof(char));

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
                        inputText = (char *)calloc(stringSize, sizeof(char));
                    }
                    else if (i == 2 && tosupress == -1)
                    {
                        supressed = false;
                        char *endptr;
                        tosupress = (int)strtol(inputText, &endptr, 10);
                        animationProgress = 0.0f;
                    }
        //*********************************************************************************************
                    else if (i==3)
                    {
                       showInsertionButtons = !showInsertionButtons;
                    }
                    if (showInsertionButtons)
        {
            DrawInsertionButtons(insertionButtons, sizeof(insertionButtons) / sizeof(insertionButtons[0]));

            for (int i = 0; i < sizeof(insertionButtons) / sizeof(insertionButtons[0]); i++)
            {
                if (CheckCollisionPointRec(GetMousePosition(), insertionButtons[i].rect))
                {
                    insertionButtons[i].color = BROWN;

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        insertionButtons[i].pressed = true;

                        if (i == 0)
                        {
                            // Handle "Enter Value" button press
                            insertionValue = GetInputValue(); // Implement this function to get user input
                        }
                        else if (i == 1)
                        {
                            // Handle "Enter Position" button press
                            insertionPosition = GetInputPosition(); // Implement this function to get user input
                        }
                        else if (i == 2)
                        {
                            // Handle "Perform Insertion" button press
                            HandleInsertion(&MaPile, insertionValue, insertionPosition);
                            showInsertionButtons = false; // Hide insertion buttons after performing insertion
                        }
                    }
                }
        //***********************************************************************************************            
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

        Rectangle inputBox = {50, 350, 150, 30};
        DrawRectangleRec(inputBox, BROWN);

        if (buttons[2].pressed)
        {
            DrawText("Press Right Key to Suppress:", 58, 400, 20, BROWN);
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
                    // supressed = true;
                }
            }
        }

        if (Pilevide(&MaPile))
        {
            if (!supressed)
            {
                DrawText("Oops  ! la valeur n'existe pas dans la pile.\n\nEntrez une autre valeur!", 58, 550, 20, BROWN);
            }
        }

        if (supressed && !Pilevide(&pile2))
        {
            DrawText("YAY! Votre valeur a ete supprimee!", 58, 450, 20, BROWN);
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
        ClearBackground(BEIGE);
        DrawText(inputText, inputBox.x + 5, inputBox.y + 5, 20, BEIGE);
        DrawPile(&MaPile, &pile2);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
